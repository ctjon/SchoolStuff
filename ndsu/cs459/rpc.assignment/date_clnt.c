#include <rpc/rpc.h>
#include "date.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

long *
bin_date_1(argp, clnt)
	void *argp;
	CLIENT *clnt;
{
	static long res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, BIN_DATE, xdr_void, argp, xdr_long, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


char **
str_date_1(argp, clnt)
	long *argp;
	CLIENT *clnt;
{
	static char *res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, STR_DATE, xdr_long, argp, xdr_wrapstring, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}

