/*
 * Chris Tjon
 * UDP/IP ping
 * CS459 Program 3
 * 9 February 1994
 * 
 * This program is a UDP/IP implementation of /etc/ping.  It is developed for
 * SunOs 4.0D_Export.  To execute type the following:
 * 
 * udp_ping <hostname>
 * 
 * type <ctrl-c> to stop the ping process
 */

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/socket.h>

#define MAX_HOST_LEN 64		/* define maximum length host name */
#define	TVAL_SIZE    4		/* 4 bytes in the 32-bit binary timeval */


void sig_abort(void);
void udp_ping(char *host);

int pkt_sent = 0;		/* number of packets sent to host */
int pkt_recd = 0;		/* number of packets echoed by host */
double min_trip = 1000000000;	/* shortest trip time in ms */
double max_trip = 0;		/* longest trip time in ms */
double sum_trip = 0;		/* summation of all trip times */
char host[MAX_HOST_LEN];	/* maximum length of a hostname */
int socket_fd;			/* socket to open to host */
extern int errno;		/* error number variable */

main(int argc, char **argv)
{
    extern char host[MAX_HOST_LEN];	/* maximum length of a hostname */

    signal(SIGINT, sig_abort);

    if (argc != 2)
	fprintf(stderr, "%s\n", "Usage: udp_ping <hostname|hostip>"), exit(1);
    else
    {
	strcpy(host, argv[1]);
	udp_ping(argv[1]);
    }
}


void udp_ping(char *host)
/*
 * Contact the time server using UDP/IP and print the result.
 */
{
    extern int pkt_sent;		/* number of packets sent to host */
    extern int pkt_recd;		/* number of packets echoed by host */
    extern double min_trip;		/* shortest trip time in ms */
    extern double max_trip;		/* longest trip time in ms */
    extern double sum_trip;		/* summation of all trip times */
    extern char host[MAX_HOST_LEN];	/* maximum length of a hostname */
    extern int socket_fd;		/* socket to open to host */
    struct timeval tptr;		/* pointer to timeval structure */
    int rbytes = TVAL_SIZE;		/* number of bytes received */
    double stime;			/* time packet sent to host */
    double rtime;			/* time packet received from host */
    unsigned int udp_seq = 0;		/* temp time variable for dgsendrecv */
    unsigned register int i;		/* counter variable */
    struct hostent *h_ent;		/* struct returned from gethostbyname */
    unsigned long addr;         	/* struct for return fr gethostbyaddr */

    /*
     * Open the socket and send an empty datagram to the server.
     */

    if (isdigit(host[0]))		/* hostname is ip number format */
    {
    	if ((addr = ntohl(inet_addr(host))) == -1)
        {
            fprintf(stderr,"%s\n","inet_addr - malformed req - aborting");
            exit(1);
	}
    	h_ent = gethostbyaddr((char *)&addr, sizeof(addr) ,AF_INET);
    }
    else				/* hostname is ip name format */
    	h_ent = gethostbyname(host); 

    if (h_ent == NULL)
	fprintf(stderr,"%s\n","error getting host by addr - aborting"),exit(1);

    printf("UDP/IP PING %s (%s): %d data bytes\n", h_ent->h_name,
	   inet_ntoa((struct in_addr *) (ntohl( h_ent->h_addr))), rbytes);
    if ((socket_fd = udp_open(host, "echo", 0, 0)) < 0)
    {
	err_ret("UDP/IP ping - udp_open error");
	return;
    }

    for (;;)
    {
	rtime = 0;
	stime = 0;
	/*
	 * get send time in u_sec
	 */
	if ((gettimeofday(&tptr, NULL)) == -1)
	    perror("udp_ping - error getting system time"), exit(1);
	else
	    /* calculate send time in u_sec */
	    stime = (double) ((tptr.tv_sec * 1000000) + tptr.tv_usec);

	/*
	 * Send a datagram, and read a response.
	 */
	pkt_sent++;
	if ((dgsendrecv(socket_fd, (char *) &udp_seq, 1, (char *) &udp_seq,
			TVAL_SIZE, (struct sockaddr *) 0, 0)) != TVAL_SIZE)
	    if (errno == EINTR)
	    {
		err_ret("udp_time: no response from server");
		close(socket_fd);
		exit(1);
	    }
	    else
		pkt_recd++;
	/*
	 * get receive time in u_sec
	 */
	if ((gettimeofday(&tptr, NULL)) == -1)
	    perror("udp_ping - error getting system time"), exit(1);
	else
	    /* calculate receive time in u_sec */
	    rtime = (double) ((tptr.tv_sec * 1000000) + tptr.tv_usec);

	/*
	 * Check for new minimum and maximum time
	 */
	if (rtime - stime < min_trip)
	    min_trip = rtime - stime;
	if (rtime - stime > max_trip)
	    max_trip = rtime - stime;
	sum_trip = sum_trip + (rtime - stime);

	/*
	 * Print Output Line
	 */
	printf("%d bytes from %s: udp_seq=%d. time=%.3f. ms\n",
	    rbytes, inet_ntoa((struct in_addr *) (ntohl(h_ent->h_addr))),
	    udp_seq++, ((rtime - stime) / 1000.0));
	for (i = 0; i < 1000000; i++);
    }
}

void sig_abort(void)
{
    extern int pkt_sent;		/* number of packets sent to host */
    extern int pkt_recd;		/* number of packets echoed by host */
    extern double min_trip;		/* shortest trip time in ms */
    extern double max_trip;		/* longest trip time in ms */
    extern double sum_trip;		/* summation of all trip times */
    extern int socket_fd;		/* socket to open to host */
    extern char host[MAX_HOST_LEN];	/* maximum length of a hostname */

    printf("----%s PING Statistics----\n", host);
    printf("%d packets transmitted, %d packets received, %d%% packet loss\n",
	   pkt_sent, pkt_recd,
    nint((double) (100 - (((double) pkt_recd / (double) pkt_sent) * 100))));
    if (pkt_recd > 0)
    {
	printf("round-trip (ms)  min/avg/max = %.3f/%.3f/%.3f\n",
	       (double) min_trip / 1000.0, ((double) (sum_trip / pkt_recd)) / 1000.0,
	       (double) max_trip / 1000.0);
    }
    close(socket_fd);
    exit(0);
}
