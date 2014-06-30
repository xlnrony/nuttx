/****************************************************************************
 * include/nuttx/net/tcp.h
 * Header file for the uIP TCP/IP stack.
 *
 * The uIP TCP/IP stack header file contains definitions for a number
 * of C macros that are used by uIP programs as well as internal uIP
 * structures, TCP/IP header structures and function declarations.
 *
 *   Copyright (C) 2007, 2009-2010, 2012-2014 Gregory Nutt. All rights
 *      reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * This logic was leveraged from uIP which also has a BSD-style license:
 *
 *   Author Adam Dunkels <adam@dunkels.com>
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

#ifndef __INCLUDE_NUTTX_NET_TCP_H
#define __INCLUDE_NUTTX_NET_TCP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#ifdef CONFIG_NET_TCP

#include <stdint.h>
#include <stdbool.h>

#include <nuttx/net/netconfig.h>
#include <nuttx/net/iob.h>
#include <nuttx/net/uip.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TCP definitions */

#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
#define TCP_CTL 0x3f

#define TCP_OPT_END     0   /* End of TCP options list */
#define TCP_OPT_NOOP    1   /* "No-operation" TCP option */
#define TCP_OPT_MSS     2   /* Maximum segment size TCP option */

#define TCP_OPT_MSS_LEN 4   /* Length of TCP MSS option. */

/* The TCP states used in the struct tcp_conn_s tcpstateflags field */

#define UIP_TS_MASK     0x0f /* Bits 0-3: TCP state */
#define UIP_CLOSED      0x00 /* The connection is not in use and available */
#define UIP_ALLOCATED   0x01 /* The connection is allocated, but not yet initialized */
#define UIP_SYN_RCVD    0x02
#define UIP_SYN_SENT    0x03
#define UIP_ESTABLISHED 0x04
#define UIP_FIN_WAIT_1  0x05
#define UIP_FIN_WAIT_2  0x06
#define UIP_CLOSING     0x07
#define UIP_TIME_WAIT   0x08
#define UIP_LAST_ACK    0x09
#define UIP_STOPPED     0x10 /* Bit 4: stopped */
                             /* Bit 5-7: Unused, but not available */

/* Flag bits in 16-bit flags+ipoffset IPv4 TCP header field */

#define UIP_TCPFLAG_RESERVED  0x8000
#define UIP_TCPFLAG_DONTFRAG  0x4000
#define UIP_TCPFLAG_MOREFRAGS 0x2000

/* TCP header sizes */

#define UIP_TCPH_LEN    20    /* Size of TCP header */
#define UIP_IPTCPH_LEN (UIP_TCPH_LEN + UIP_IPH_LEN)    /* Size of IP + TCP header */
#define UIP_TCPIP_HLEN UIP_IPTCPH_LEN

/* Initial minimum MSS according to RFC 879
 *
 * There have been some assumptions made about using other than the
 * default size for datagrams with some unfortunate results.
 *
 *     HOSTS MUST NOT SEND DATAGRAMS LARGER THAN 576 OCTETS UNLESS THEY
 *     HAVE SPECIFIC KNOWLEDGE THAT THE DESTINATION HOST IS PREPARED TO
 *     ACCEPT LARGER DATAGRAMS.
 *
 * This is a long established rule.
 */

#if UIP_TCP_MSS > 576
#  define UIP_TCP_INITIAL_MSS 576
#else
#  define UIP_TCP_INITIAL_MSS UIP_TCP_MSS
#endif

#ifdef CONFIG_NET_TCP_WRITE_BUFFERS
/* TCP write buffer access macros */

#  define WRB_SEQNO(wrb)          ((wrb)->wb_seqno)
#  define WRB_PKTLEN(wrb)         ((wrb)->wb_iob->io_pktlen)
#  define WRB_SENT(wrb)           ((wrb)->wb_sent)
#  define WRB_NRTX(wrb)           ((wrb)->wb_nrtx)
#  define WRB_IOB(wrb)            ((wrb)->wb_iob)
#  define WRB_COPYOUT(wrb,dest,n) (iob_copyout(dest,(wrb)->wb_iob,(n),0))
#  define WRB_COPYIN(wrb,src,n)   (iob_copyin((wrb)->wb_iob,src,(n),0,false))

#  define WRB_TRIM(wrb,n) \
  do { (wrb)->wb_iob = iob_trimhead((wrb)->wb_iob,(n)); } while (0)

#ifdef CONFIG_DEBUG
#  define WRB_DUMP(msg,wrb,len,offset) \
     tcp_wrbuffer_dump(msg,wrb,len,offset)
#else
#  define WRB_DUMP(msg,wrb,len,offset)
#endif
#endif

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

/* Representation of a uIP TCP connection.
 *
 * The tcp_conn_s structure is used for identifying a connection. All
 * but one field in the structure are to be considered read-only by an
 * application. The only exception is the 'private' fields whose purpose
 * is to let the application store application-specific state (e.g.,
 * file pointers) for the connection.
 */

struct net_driver_s;      /* Forward reference */
struct devif_callback_s;  /* Forward reference */
struct tcp_backlog_s;     /* Forward reference */

struct tcp_conn_s
{
  dq_entry_t node;        /* Implements a doubly linked list */
  net_ipaddr_t ripaddr;   /* The IP address of the remote host */
  uint8_t  rcvseq[4];     /* The sequence number that we expect to
                           * receive next */
  uint8_t  sndseq[4];     /* The sequence number that was last sent by us */
  uint8_t  crefs;         /* Reference counts on this instance */
  uint8_t  sa;            /* Retransmission time-out calculation state
                           * variable */
  uint8_t  sv;            /* Retransmission time-out calculation state
                           * variable */
  uint8_t  rto;           /* Retransmission time-out */
  uint8_t  tcpstateflags; /* TCP state and flags */
  uint8_t  timer;         /* The retransmission timer (units: half-seconds) */
  uint8_t  nrtx;          /* The number of retransmissions for the last
                           * segment sent */
  uint16_t lport;         /* The local TCP port, in network byte order */
  uint16_t rport;         /* The remoteTCP port, in network byte order */
  uint16_t mss;           /* Current maximum segment size for the
                           * connection */
  uint16_t winsize;       /* Current window size of the connection */
#ifdef CONFIG_NET_TCP_WRITE_BUFFERS
  uint32_t unacked;       /* Number bytes sent but not yet ACKed */
#else
  uint16_t unacked;       /* Number bytes sent but not yet ACKed */
#endif

  /* Read-ahead buffering.
   *
   *   readahead - A singly linked list of type struct iob_qentry_s
   *               where the TCP/IP read-ahead data is retained.
   */

#ifdef CONFIG_NET_TCP_READAHEAD
  struct iob_queue_s readahead;   /* Read-ahead buffering */
#endif

  /* Write buffering
   *
   *   write_q   - The queue of unsent I/O buffers.  The head of this
   *               list may be partially sent.  FIFO ordering.
   *   unacked_q - A queue of completely sent, but unacked I/O buffer
   *               chains.  Sequence number ordering.
   */

#ifdef CONFIG_NET_TCP_WRITE_BUFFERS
  sq_queue_t write_q;     /* Write buffering for segments */
  sq_queue_t unacked_q;   /* Write buffering for un-ACKed segments */
  uint16_t   expired;     /* Number segments retransmitted but not yet ACKed,
                           * it can only be updated at UIP_ESTABLISHED state */
  uint16_t   sent;        /* The number of bytes sent (ACKed and un-ACKed) */
  uint32_t   isn;         /* Initial sequence number */
#endif

  /* Listen backlog support
   *
   *   blparent - The backlog parent.  If this connection is backlogged,
   *     this field will be non-null and will refer to the TCP connection
   *     structure in which this connection is backlogged.
   *   backlog - The pending connection backlog.  If this connection is
   *     configured as a listener with backlog, then this refers to the
   *     struct tcp_backlog_s tear-off structure that manages that backlog.
   */

#ifdef CONFIG_NET_TCPBACKLOG
  FAR struct tcp_conn_s    *blparent;
  FAR struct tcp_backlog_s *backlog;
#endif

  /* Application callbacks:
   *
   * Data transfer events are retained in 'list'.  Event handlers in 'list'
   * are called for events specified in the flags set within struct
   * devif_callback_s
   *
   * When an callback is executed from 'list', the input flags are normally
   * returned, however, the implementation may set one of the following:
   *
   *   UIP_CLOSE   - Gracefully close the current connection
   *   UIP_ABORT   - Abort (reset) the current connection on an error that
   *                 prevents UIP_CLOSE from working.
   *
   * And/Or set/clear the following:
   *
   *   UIP_NEWDATA - May be cleared to indicate that the data was consumed
   *                 and that no further process of the new data should be
   *                 attempted.
   *   UIP_SNDACK  - If UIP_NEWDATA is cleared, then UIP_SNDACK may be set
   *                 to indicate that an ACK should be included in the response.
   *                 (In UIP_NEWDATA is cleared bu UIP_SNDACK is not set, then
   *                 dev->d_len should also be cleared).
   */

  FAR struct devif_callback_s *list;

  /* accept() is called when the TCP logic has created a connection */

  FAR void *accept_private;
  int (*accept)(FAR struct tcp_conn_s *listener, FAR struct tcp_conn_s *conn);

  /* connection_event() is called on any of the subset of connection-related
   * events.
   */

  FAR void *connection_private;
  void (*connection_event)(FAR struct tcp_conn_s *conn, uint16_t flags);
};

/* This structure supports TCP write buffering */

#ifdef CONFIG_NET_TCP_WRITE_BUFFERS
struct tcp_wrbuffer_s
{
  sq_entry_t wb_node;      /* Supports a singly linked list */
  uint32_t   wb_seqno;     /* Sequence number of the write segment */
  uint16_t   wb_sent;      /* Number of bytes sent from the I/O buffer chain */
  uint8_t    wb_nrtx;      /* The number of retransmissions for the last
                            * segment sent */
  struct iob_s *wb_iob;    /* Head of the I/O buffer chain */
};
#endif

/* Support for listen backlog:
 *
 *   struct tcp_blcontainer_s describes one backlogged connection
 *   struct tcp_backlog_s is a "tear-off" describing all backlog for a
 *      listener connection
 */

#ifdef CONFIG_NET_TCPBACKLOG
struct tcp_blcontainer_s
{
  sq_entry_t bc_node;             /* Implements a singly linked list */
  FAR struct tcp_conn_s *bc_conn; /* Holds reference to the new connection structure */
};

struct tcp_backlog_s
{
  sq_queue_t bl_free;             /* Implements a singly-linked list of free containers */
  sq_queue_t bl_pending;          /* Implements a singly-linked list of pending connections */
};
#endif

/* The structure holding the TCP/IP statistics that are gathered if
 * CONFIG_NET_STATISTICS is defined.
 */

#ifdef CONFIG_NET_STATISTICS
struct tcp_stats_s
{
  net_stats_t drop;       /* Number of dropped TCP segments */
  net_stats_t recv;       /* Number of received TCP segments */
  net_stats_t sent;       /* Number of sent TCP segments */
  net_stats_t chkerr;     /* Number of TCP segments with a bad checksum */
  net_stats_t ackerr;     /* Number of TCP segments with a bad ACK number */
  net_stats_t rst;        /* Number of received TCP RST (reset) segments */
  net_stats_t rexmit;     /* Number of retransmitted TCP segments */
  net_stats_t syndrop;    /* Number of dropped SYNs due to too few
                             available connections */
  net_stats_t synrst;     /* Number of SYNs for closed ports triggering a RST */
};
#endif

/* The TCP and IP headers */

struct tcp_iphdr_s
{
#ifdef CONFIG_NET_IPv6

  /* IPv6 Ip header */

  uint8_t  vtc;             /* Bits 0-3: version, bits 4-7: traffic class (MS) */
  uint8_t  tcf;             /* Bits 0-3: traffic class (LS), 4-bits: flow label (MS) */
  uint16_t flow;            /* 16-bit flow label (LS) */
  uint8_t  len[2];          /* 16-bit Payload length */
  uint8_t  proto;           /*  8-bit Next header (same as IPv4 protocol field) */
  uint8_t  ttl;             /*  8-bit Hop limit (like IPv4 TTL field) */
  net_ip6addr_t srcipaddr;  /* 128-bit Source address */
  net_ip6addr_t destipaddr; /* 128-bit Destination address */

#else /* CONFIG_NET_IPv6 */

  /* IPv4 IP header */

  uint8_t  vhl;             /*  8-bit Version (4) and header length (5 or 6) */
  uint8_t  tos;             /*  8-bit Type of service (e.g., 6=TCP) */
  uint8_t  len[2];          /* 16-bit Total length */
  uint8_t  ipid[2];         /* 16-bit Identification */
  uint8_t  ipoffset[2];     /* 16-bit IP flags + fragment offset */
  uint8_t  ttl;             /*  8-bit Time to Live */
  uint8_t  proto;           /*  8-bit Protocol */
  uint16_t ipchksum;        /* 16-bit Header checksum */
  uint16_t srcipaddr[2];    /* 32-bit Source IP address */
  uint16_t destipaddr[2];   /* 32-bit Destination IP address */

#endif /* CONFIG_NET_IPv6 */

  /* TCP header */

  uint16_t srcport;
  uint16_t destport;
  uint8_t  seqno[4];
  uint8_t  ackno[4];
  uint8_t  tcpoffset;
  uint8_t  flags;
  uint8_t  wnd[2];
  uint16_t tcpchksum;
  uint8_t  urgp[2];
  uint8_t  optdata[4];
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/* uIP application functions
 *
 * Functions used by an application running of top of uIP. This includes
 * functions for opening and closing connections, sending and receiving
 * data, etc.
 *
 * Find a free connection structure and allocate it for use. This is
 * normally something done by the implementation of the socket() API
 */

struct tcp_conn_s *tcp_alloc(void);

/* Free a connection structure that is no longer in use. This should
 * be done by the implementation of close()
 */

void tcp_free(FAR struct tcp_conn_s *conn);

/* Bind a TCP connection to a local address */

#ifdef CONFIG_NET_IPv6
int tcp_bind(FAR struct tcp_conn_s *conn,
             FAR const struct sockaddr_in6 *addr);
#else
int tcp_bind(FAR struct tcp_conn_s *conn,
             FAR const struct sockaddr_in *addr);
#endif

/* This function implements the UIP specific parts of the standard
 * TCP connect() operation:  It connects to a remote host using TCP.
 *
 * This function is used to start a new connection to the specified
 * port on the specied host. It uses the connection structure that was
 * allocated by a preceding socket() call.  It sets the connection to
 * the SYN_SENT state and sets the retransmission timer to 0. This will
 * cause a TCP SYN segment to be sent out the next time this connection
 * is periodically processed, which usually is done within 0.5 seconds
 * after the call to tcp_connect().
 *
 * This function is called from normal user level code.
 */

#ifdef CONFIG_NET_IPv6
int tcp_connect(FAR struct tcp_conn_s *conn,
                FAR const struct sockaddr_in6 *addr);
#else
int tcp_connect(FAR struct tcp_conn_s *conn,
                FAR const struct sockaddr_in *addr);
#endif

/* Start listening to the port bound to the specified TCP connection */

int tcp_listen(FAR struct tcp_conn_s *conn);

/* Stop listening to the port bound to the specified TCP connection */

int tcp_unlisten(FAR struct tcp_conn_s *conn);

/* Backlog support */

#ifdef CONFIG_NET_TCPBACKLOG
/* APIs to create and terminate TCP backlog support */

int tcp_backlogcreate(FAR struct tcp_conn_s *conn, int nblg);
int tcp_backlogdestroy(FAR struct tcp_conn_s *conn);

/* APIs to manage individual backlog actions */

int tcp_backlogadd(FAR struct tcp_conn_s *conn,
                   FAR struct tcp_conn_s *blconn);
#ifndef CONFIG_DISABLE_POLL
bool tcp_backlogavailable(FAR struct tcp_conn_s *conn);
#else
#  define tcp_backlogavailable(conn)   (false);
#endif
FAR struct tcp_conn_s *tcp_backlogremove(FAR struct tcp_conn_s *conn);
int tcp_backlogdelete(FAR struct tcp_conn_s *conn,
                      FAR struct tcp_conn_s *blconn);

#else
#  define tcp_backlogcreate(conn,nblg) (-ENOSYS)
#  define tcp_backlogdestroy(conn)     (-ENOSYS)
#  define tcp_backlogadd(conn,blconn)  (-ENOSYS)
#  define tcp_backlogavailable(conn)   (false);
#  define tcp_backlogremove(conn)      (NULL)
#endif

/* Tell the sending host to stop sending data.
 *
 * This function will close our receiver's window so that we stop
 * receiving data for the current connection.
 */

#define uip_stop(conn) ((conn)->tcpstateflags |= UIP_STOPPED)

/* Find out if the current connection has been previously stopped with
 * uip_stop().
 */

#define uip_stopped(conn) ((conn)->tcpstateflags & UIP_STOPPED)

/* Restart the current connection, if is has previously been stopped
 * with uip_stop().
 *
 * This function will open the receiver's window again so that we start
 * receiving data for the current connection.
 */

#define uip_restart(conn,f) \
  do { \
    (f) |= UIP_NEWDATA; \
    (conn)->tcpstateflags &= ~UIP_STOPPED; \
  } while (0)

/* Get the current maximum segment size that can be sent on the current
 * connection.
 */

#define uip_mss(conn) ((conn)->mss)

#endif /* CONFIG_NET_TCP */
#endif /* __INCLUDE_NUTTX_NET_TCP_H */
