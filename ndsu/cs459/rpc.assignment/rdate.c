#include "date.h"
#include <stdio.h>
#include <rpc/rpc.h>

main(int argc, char *argv[]) {
	CLIENT		*cl;			/* rpc handle */
	char		*server;		
	long		*lresult;		/* return value from bin_date_1 */
	char		**sresult;		/* return value from str_date_1 */

	if (argc != 2) {
		fprintf(stderr,"usage: %s hostname\n",argv[0]);
		exit(1);
	}

	server = argv[1];

	/* create client */

	if ( (cl = clnt_create(server, DATE_PROG, DATE_VERS, "udp")) == NULL ) {
		/* couldn't establish connection */

		clnt_pcreateerror(server);
		exit(2);
	}

	if ( (lresult = bin_date_1(NULL,cl)) == NULL ) {
		clnt_perror(cl, server);
		exit(3);
	}

	printf("time on host %s = %ld\n",server,*lresult);

	if ( (sresult = str_date_1(lresult,cl)) == NULL ) {
		clnt_perror(cl, server);
		exit(4);
	}

	printf("time on host %s = %s\n",server,*sresult);

	clnt_destroy(cl);

	exit(0);

}
