#include <stdio.h>

#include <signal.h>


void cleanup();



main(){

	signal( SIGINT, cleanup );	/* Hook up signal handler */

	printf("Press ^C to exit...\n");
	pause();
}



void cleanup(){
	printf("In cleanup, exiting\n");
	exit(0);
}
