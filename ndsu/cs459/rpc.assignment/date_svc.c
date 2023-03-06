#include <stdio.h>
#include <rpc/rpc.h>
#include "date.h"

static void date_prog_1();

main()
{
	SVCXPRT *transp;

	(void)pmap_unset(DATE_PROG, DATE_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create udp service.\n");
		exit(1);
	}
	if (!svc_register(transp, DATE_PROG, DATE_VERS, date_prog_1, IPPROTO_UDP)) {
		(void)fprintf(stderr, "unable to register (DATE_PROG, DATE_VERS, udp).\n");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create tcp service.\n");
		exit(1);
	}
	if (!svc_register(transp, DATE_PROG, DATE_VERS, date_prog_1, IPPROTO_TCP)) {
		(void)fprintf(stderr, "unable to register (DATE_PROG, DATE_VERS, tcp).\n");
		exit(1);
	}
	svc_run();
	(void)fprintf(stderr, "svc_run returned\n");
	exit(1);
}

static void
date_prog_1(rqstp, transp)
	struct svc_req *rqstp;
	SVCXPRT *transp;
{
	union {
		long str_date_1_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void)svc_sendreply(transp, xdr_void, (char *)NULL);
		return;

	case BIN_DATE:
		xdr_argument = xdr_void;
		xdr_result = xdr_long;
		local = (char *(*)()) bin_date_1;
		break;

	case STR_DATE:
		xdr_argument = xdr_long;
		xdr_result = xdr_wrapstring;
		local = (char *(*)()) str_date_1;
		break;

	default:
		svcerr_noproc(transp);
		return;
	}
	bzero((char *)&argument, sizeof(argument));
	if (!svc_getargs(transp, xdr_argument, &argument)) {
		svcerr_decode(transp);
		return;
	}
	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
		exit(1);
	}
}

