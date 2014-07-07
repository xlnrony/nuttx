/****************************************************************************
 * net/arp/arm_inout.c
 * Implementation of the ARP Address Resolution Protocol.
 *
 *   Copyright (C) 2007-2011, 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Based on uIP which also has a BSD style license:
 *
 *   Author: Adam Dunkels <adam@dunkels.com>
 *   Copyright (c) 2001-2003, Adam Dunkels.
 *   All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* The Address Resolution Protocol ARP is used for mapping between IP
 * addresses and link level addresses such as the Ethernet MAC
 * addresses. ARP uses broadcast queries to ask for the link level
 * address of a known IP address and the host which is configured with
 * the IP address for which the query was meant, will respond with its
 * link level address.
 *
 * Note: This ARP implementation only supports Ethernet.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#ifdef CONFIG_NET

#include <sys/ioctl.h>
#include <stdint.h>
#include <string.h>
#include <debug.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <net/ethernet.h>
#include <nuttx/net/netconfig.h>
#include <nuttx/net/netdev.h>
#include <nuttx/net/arp.h>
#include <nuttx/net/ip.h>

#include "netdev/netdev.h"
#include "route/route.h"
#include "arp/arp.h"

#ifdef CONFIG_NET_ARP

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define ARP_REQUEST    1
#define ARP_REPLY      2

#define ARP_HWTYPE_ETH 1

#define RASIZE         4  /* Size of ROUTER ALERT */

#define ETHBUF        ((struct eth_hdr_s *)&dev->d_buf[0])
#define ARPBUF        ((struct arp_hdr_s *)&dev->d_buf[NET_LL_HDRLEN])
#define IPBUF         ((struct arp_iphdr_s *)&dev->d_buf[NET_LL_HDRLEN])

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* ARP header -- Size 28 bytes */

struct arp_hdr_s
{
  uint16_t ah_hwtype;        /* 16-bit Hardware type (Ethernet=0x001) */
  uint16_t ah_protocol;      /* 16-bit Protocol type (IP=0x0800) */
  uint8_t  ah_hwlen;         /*  8-bit Hardware address size (6) */
  uint8_t  ah_protolen;      /*  8-bit Procotol address size (4) */
  uint16_t ah_opcode;        /* 16-bit Operation */
  uint8_t  ah_shwaddr[6];    /* 48-bit Sender hardware address */
  uint16_t ah_sipaddr[2];    /* 32-bit Sender IP adress */
  uint8_t  ah_dhwaddr[6];    /* 48-bit Target hardware address */
  uint16_t ah_dipaddr[2];    /* 32-bit Target IP address */
};

/* IP header -- Size 20 or 24 bytes */

struct arp_iphdr_s
{
  uint8_t  eh_vhl;           /*  8-bit Version (4) and header length (5 or 6) */
  uint8_t  eh_tos;           /*  8-bit Type of service (e.g., 6=TCP) */
  uint8_t  eh_len[2];        /* 16-bit Total length */
  uint8_t  eh_ipid[2];       /* 16-bit Identification */
  uint8_t  eh_ipoffset[2];   /* 16-bit IP flags + fragment offset */
  uint8_t  eh_ttl;           /*  8-bit Time to Live */
  uint8_t  eh_proto;         /*  8-bit Protocol */
  uint16_t eh_ipchksum;      /* 16-bit Header checksum */
  uint16_t eh_srcipaddr[2];  /* 32-bit Source IP address */
  uint16_t eh_destipaddr[2]; /* 32-bit Destination IP address */
  uint16_t eh_ipoption[2];   /* (optional) */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Support for broadcast address */

static const struct ether_addr g_broadcast_ethaddr =
  {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}};
static const uint16_t g_broadcast_ipaddr[2] = {0xffff, 0xffff};

/* Support for IGMP multicast addresses.
 *
 * Well-known ethernet multicast address:
 *
 * ADDRESS           TYPE   USAGE
 * 01-00-0c-cc-cc-cc 0x0802 CDP (Cisco Discovery Protocol), VTP (Virtual Trunking Protocol)
 * 01-00-0c-cc-cc-cd 0x0802 Cisco Shared Spanning Tree Protocol Address
 * 01-80-c2-00-00-00 0x0802 Spanning Tree Protocol (for bridges) IEEE 802.1D
 * 01-80-c2-00-00-02 0x0809 Ethernet OAM Protocol IEEE 802.3ah
 * 01-00-5e-xx-xx-xx 0x0800 IPv4 IGMP Multicast Address
 * 33-33-00-00-00-00 0x86DD IPv6 Neighbor Discovery
 * 33-33-xx-xx-xx-xx 0x86DD IPv6 Multicast Address (RFC3307)
 *
 * The following is the first three octects of the IGMP address:
 */

#if defined(CONFIG_NET_IGMP) && !defined(CONFIG_NET_IPv6)
static const uint8_t g_multicast_ethaddr[3] = {0x01, 0x00, 0x5e};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#if defined(CONFIG_NET_DUMPARP) && defined(CONFIG_DEBUG)
static void arp_dump(FAR struct arp_hdr_s *arp)
{
  nlldbg("  HW type: %04x Protocol: %04x\n",
         arp->ah_hwtype, arp->ah_protocol);\
  nlldbg("  HW len: %02x Proto len: %02x Operation: %04x\n",
         arp->ah_hwlen, arp->ah_protolen, arp->ah_opcode);
  nlldbg("  Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x IP: %d.%d.%d.%d\n",
         arp->ah_shwaddr[0], arp->ah_shwaddr[1], arp->ah_shwaddr[2],
         arp->ah_shwaddr[3], arp->ah_shwaddr[4], arp->ah_shwaddr[5],
         arp->ah_sipaddr[0] & 0xff, arp->ah_sipaddr[0] >> 8,
         arp->ah_sipaddr[1] & 0xff, arp->ah_sipaddr[1] >> 8);
  nlldbg("  Dest MAC:   %02x:%02x:%02x:%02x:%02x:%02x IP: %d.%d.%d.%d\n",
         arp->ah_dhwaddr[0], arp->ah_dhwaddr[1], arp->ah_dhwaddr[2],
         arp->ah_dhwaddr[3], arp->ah_dhwaddr[4], arp->ah_dhwaddr[5],
         arp->ah_dipaddr[0] & 0xff, arp->ah_dipaddr[0] >> 8,
         arp->ah_dipaddr[1] & 0xff, arp->ah_dipaddr[1] >> 8);
}
#else
# define arp_dump(arp)
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arp_ipin
 *
 * Description:
 *   The arp_ipin() function should be called by Ethernet device drivers
 *   whenever an IP packet arrives from the network.  The function will
 *   check if the address is in the ARP cache, and if so the ARP cache entry
 *   will be refreshed. If no ARP cache entry was found, a new one is created.
 *
 *   This function expects that an IP packet with an Ethernet header is
 *   present in the d_buf buffer and that the length of the packet is in the
 *   d_len field.
 *
 ****************************************************************************/

#ifdef CONFIG_NET_ARP_IPIN
void arp_ipin(FAR struct net_driver_s *dev)
{
  in_addr_t srcipaddr;

  /* Only insert/update an entry if the source IP address of the incoming IP
   * packet comes from a host on the local network.
   */

  srcipaddr = net_ip4addr_conv32(IPBUF->eh_srcipaddr);
  if (net_ipaddr_maskcmp(srcipaddr, dev->d_ipaddr, dev->d_netmask))
    {
      arp_update(IPBUF->eh_srcipaddr, ETHBUF->src);
    }
}
#endif /* CONFIG_NET_ARP_IPIN */

/****************************************************************************
 * Name: arp_arpin
 *
 * Description:
 *   This function should be called by the Ethernet device driver when an ARP
 *   packet has been received.   The function will act differently
 *   depending on the ARP packet type: if it is a reply for a request
 *   that we previously sent out, the ARP cache will be filled in with
 *   the values from the ARP reply.  If the incoming ARP packet is an ARP
 *   request for our IP address, an ARP reply packet is created and put
 *   into the d_buf[] buffer.
 *
 *   On entry, this function expects that an ARP packet with a prepended
 *   Ethernet header is present in the d_buf[] buffer and that the length of
 *   the packet is set in the d_len field.
 *
 *   When the function returns, the value of the field d_len indicates whether
 *   the device driver should send out the ARP reply packet or not. If d_len
 *   is zero, no packet should be sent; If d_len is non-zero, it contains the
 *   length of the outbound packet that is present in the d_buf[] buffer.
 *
 ****************************************************************************/

void arp_arpin(FAR struct net_driver_s *dev)
{
  FAR struct arp_hdr_s *parp = ARPBUF;
  in_addr_t ipaddr;

  if (dev->d_len < (sizeof(struct arp_hdr_s) + NET_LL_HDRLEN))
    {
      nlldbg("Too small\n");
      dev->d_len = 0;
      return;
    }

  dev->d_len = 0;

  ipaddr = net_ip4addr_conv32(parp->ah_dipaddr);
  switch(parp->ah_opcode)
    {
      case HTONS(ARP_REQUEST):
        nllvdbg("ARP request for IP %04lx\n", (long)ipaddr);

        /* ARP request. If it asked for our address, we send out a reply. */

        if (net_ipaddr_cmp(ipaddr, dev->d_ipaddr))
          {
            struct eth_hdr_s *peth = ETHBUF;

            /* First, we register the one who made the request in our ARP
             * table, since it is likely that we will do more communication
             * with this host in the future.
             */

            arp_update(parp->ah_sipaddr, parp->ah_shwaddr);

            parp->ah_opcode = HTONS(ARP_REPLY);
            memcpy(parp->ah_dhwaddr, parp->ah_shwaddr, ETHER_ADDR_LEN);
            memcpy(parp->ah_shwaddr, dev->d_mac.ether_addr_octet, ETHER_ADDR_LEN);
            memcpy(peth->src, dev->d_mac.ether_addr_octet, ETHER_ADDR_LEN);
            memcpy(peth->dest, parp->ah_dhwaddr, ETHER_ADDR_LEN);

            parp->ah_dipaddr[0] = parp->ah_sipaddr[0];
            parp->ah_dipaddr[1] = parp->ah_sipaddr[1];
            net_ipaddr_hdrcopy(parp->ah_sipaddr, &dev->d_ipaddr);
            arp_dump(parp);

            peth->type          = HTONS(ETHTYPE_ARP);
            dev->d_len          = sizeof(struct arp_hdr_s) + NET_LL_HDRLEN;
          }
        break;

      case HTONS(ARP_REPLY):
        nllvdbg("ARP reply for IP %04lx\n", (long)ipaddr);

        /* ARP reply. We insert or update the ARP table if it was meant
         * for us.
         */

        if (net_ipaddr_cmp(ipaddr, dev->d_ipaddr))
          {
            arp_update(parp->ah_sipaddr, parp->ah_shwaddr);
          }
        break;
    }
}

/****************************************************************************
 * Name: arp_out
 *
 * Description:
 *   This function should be called before sending out an IP packet. The
 *   function checks the destination IP address of the IP packet to see
 *   what Ethernet MAC address that should be used as a destination MAC
 *   address on the Ethernet.
 *
 *   If the destination IP address is in the local network (determined
 *   by logical ANDing of netmask and our IP address), the function
 *   checks the ARP cache to see if an entry for the destination IP
 *   address is found.  If so, an Ethernet header is pre-pended at the
 *   beginning of the packet and the function returns.
 *
 *   If no ARP cache entry is found for the destination IP address, the
 *   packet in the d_buf[] is replaced by an ARP request packet for the
 *   IP address. The IP packet is dropped and it is assumed that the
 *   higher level protocols (e.g., TCP) eventually will retransmit the
 *   dropped packet.
 *
 *   Upon return in either the case, a packet to be sent is present in the
 *   d_buf[] buffer and the d_len field holds the length of the Ethernet
 *   frame that should be transmitted.
 *
 ****************************************************************************/

void arp_out(FAR struct net_driver_s *dev)
{
  FAR const struct arp_entry *tabptr = NULL;
  FAR struct arp_hdr_s       *parp   = ARPBUF;
  FAR struct eth_hdr_s       *peth   = ETHBUF;
  FAR struct arp_iphdr_s     *pip    = IPBUF;
  in_addr_t                   ipaddr;
  in_addr_t                   destipaddr;

#ifdef CONFIG_NET_PKT
  /* Skip sending ARP requests when the frame to be transmitted was
   * written into a packet socket.
   */

  if ((dev->d_flags & IFF_NOARP) == IFF_NOARP)
    {
      return;
    }
#endif

  /* Find the destination IP address in the ARP table and construct
   * the Ethernet header. If the destination IP address isn't on the
   * local network, we use the default router's IP address instead.
   *
   * If not ARP table entry is found, we overwrite the original IP
   * packet with an ARP request for the IP address.
   */

  /* First check if destination is a local broadcast. */

  if (net_ipaddr_hdrcmp(pip->eh_destipaddr, g_broadcast_ipaddr))
    {
      memcpy(peth->dest, g_broadcast_ethaddr.ether_addr_octet, ETHER_ADDR_LEN);
    }

#if defined(CONFIG_NET_IGMP) && !defined(CONFIG_NET_IPv6)
  /* Check if the destination address is a multicast address
   *
   * - IPv4: multicast addresses lie in the class D group -- The address range
   *   224.0.0.0 to 239.255.255.255 (224.0.0.0/4)
   *
   * - IPv6 multicast addresses are have the high-order octet of the
   *   addresses=0xff (ff00::/8.)
   */

 else if (NTOHS(pip->eh_destipaddr[0]) >= 0xe000 &&
          NTOHS(pip->eh_destipaddr[0]) <= 0xefff)
    {
      /* Build the well-known IPv4 IGMP Ethernet address.  The first
       * three bytes are fixed; the final three variable come from the
       * last three bytes of the IP address.
       */

      FAR const uint8_t *ip = ((uint8_t*)pip->eh_destipaddr) + 1;
      memcpy(peth->dest,  g_multicast_ethaddr, 3);
      memcpy(&peth->dest[3], ip, 3);
    }
#endif
  else
    {
      /* Check if the destination address is on the local network. */

      destipaddr = net_ip4addr_conv32(pip->eh_destipaddr);
      if (!net_ipaddr_maskcmp(destipaddr, dev->d_ipaddr, dev->d_netmask))
        {
          /* Destination address is not on the local network */

#ifdef CONFIG_NET_ROUTE
          /* We have a routing table.. find the correct router to use in
           * this case (or, as a fall-back, use the device's default router
           * address).  We will use the router IP address instead of the
           * destination address when determining the MAC address.
           */

          netdev_router(dev, destipaddr, &ipaddr);
#else
          /* Use the device's default router IP address instead of the
           * destination address when determining the MAC address.
           */

          net_ipaddr_copy(ipaddr, dev->d_draddr);
#endif
        }
      else
        {
          /* Else, we use the destination IP address. */

          net_ipaddr_copy(ipaddr, destipaddr);
        }

      /* Check if we already have this destination address in the ARP table */

      tabptr = arp_find(ipaddr);
      if (!tabptr)
        {
           nllvdbg("ARP request for IP %04lx\n", (long)ipaddr);

          /* The destination address was not in our ARP table, so we
           * overwrite the IP packet with an ARP request.
           */

          memset(peth->dest, 0xff, ETHER_ADDR_LEN);
          memset(parp->ah_dhwaddr, 0x00, ETHER_ADDR_LEN);
          memcpy(peth->src, dev->d_mac.ether_addr_octet, ETHER_ADDR_LEN);
          memcpy(parp->ah_shwaddr, dev->d_mac.ether_addr_octet, ETHER_ADDR_LEN);

          net_ipaddr_hdrcopy(parp->ah_dipaddr, &ipaddr);
          net_ipaddr_hdrcopy(parp->ah_sipaddr, &dev->d_ipaddr);

          parp->ah_opcode   = HTONS(ARP_REQUEST);
          parp->ah_hwtype   = HTONS(ARP_HWTYPE_ETH);
          parp->ah_protocol = HTONS(ETHTYPE_IP);
          parp->ah_hwlen    = ETHER_ADDR_LEN;
          parp->ah_protolen = 4;
          arp_dump(parp);

          peth->type        = HTONS(ETHTYPE_ARP);
          dev->d_len        = sizeof(struct arp_hdr_s) + NET_LL_HDRLEN;
          return;
        }

      /* Build an Ethernet header. */

      memcpy(peth->dest, tabptr->at_ethaddr.ether_addr_octet, ETHER_ADDR_LEN);
    }

  /* Finish populating the Ethernet header */

  memcpy(peth->src, dev->d_mac.ether_addr_octet, ETHER_ADDR_LEN);
  peth->type  = HTONS(ETHTYPE_IP);
  dev->d_len += NET_LL_HDRLEN;
}

#endif /* CONFIG_NET_ARP */
#endif /* CONFIG_NET */
