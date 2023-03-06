/* THREADS.H */

#ifndef __THREADSH__
#define __THREADSH__

#include <lwp/lwp.h>
#include <lwp/stackdep.h>
#include "maxprio.h"
#include "sched.h"
#include "tg.h"

#define SCHEDP 2
#define NUM_STACKS 5
#define STACK_BYTES 1000

thread_t sched_id;

void process1(void);
void process2(void);
void process3(void);
void process4(void);
void start_procs(int argc, char *argv[]);

#endif				/* __THREADS__ */
