/*
 * File: messages2.c
 *
 * Another example of message passing between threads using the Lighweight
 * Process library on the Solbourne.  This one has multiple processes
 * sending messages to a port, which serializes them based on their contents.
 *
 * To compile, type the following at the Unix prompt:
 *	gcc -o messages2 messages2.c -llwp
 *
 * 90Feb22 BCP Created from the Solbourne manual, pages 6-12 to 6-13.
 * 93Jan25 DMR Converted to Standard C.
 */

#include <stdio.h>
#include <lwp/lwp.h>
#include <lwp/stackdep.h>

thread_t pt;

typedef struct port_msg {
	int order;
	char *msg;
} port_msg;

#define MAXPRIO 10


int process( int );
int port( void );

int
main( int argc, char **argv ){

	(void)pod_setmaxpri(MAXPRIO);
	lwp_setstkcache(1000, 3);

	/* Argument to new thread is the serialization order number. */
	lwp_create((thread_t *)0, process, MINPRIO, 0, lwp_newstk(), 1, 3);
	lwp_create((thread_t *)0, process, MINPRIO, 0, lwp_newstk(), 1, 0);
	lwp_create((thread_t *)0, process, MINPRIO, 0, lwp_newstk(), 1, 2);
	lwp_create((thread_t *)0, process, MINPRIO, 0, lwp_newstk(), 1, 1);
	lwp_create(&pt, port, MAXPRIO, 0, lwp_newstk(), 0);
	exit(0);
}

int process( int id ){
	port_msg m;
	char buf[10];

	m.order = id;
	m.msg = buf;
	printf("sending %d\n", id);
	msg_send(pt, (char *)&m, sizeof(port_msg), 0, 0);
	printf("%d replied to\n", id);
}

/*
 * Collect messages in any order, process them in order.
 */
int
port( void ){
	thread_t sender;
	char *arg;
	int asz;
	port_msg *request;
	thread_t senders[4];
	int i;

	for (i = 0; i < 4; i++)
	{	/* convenient way to recieve from any sender */
		MSG_RECVALL(&sender, &arg, &asz, 0, 0, INFINITY);
		request = (port_msg *)arg;
		printf("got %d\n", request->order);
		senders[request->order] = sender;
	}
	for (i = 0; i < 4; i++)
		msg_reply(senders[i]);
}
