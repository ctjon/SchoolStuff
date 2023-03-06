#include <rpc/rpc.h>
#include "date.h"

long *bin_date_1() {

	static long timeval;
	long time();

	timeval = time((long *) 0);

	return( &timeval);

}


char **str_date_1(long *bintime) {

	static char *ptr;
	char *ctime();

	ptr = ctime(bintime);

	return (&ptr);

}
