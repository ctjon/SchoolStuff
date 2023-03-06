From roehrich Wed Mar 17 22:55:44 1993
Received: by plains.NoDak.edu; Wed, 17 Mar 1993 22:55:43 -0600
Date: Wed, 17 Mar 1993 22:55:43 -0600
From: Dean Roehrich <roehrich>
Message-Id: <199303180455.AA20621@plains.NoDak.edu>
To: kroh, tjon
Status: R

Scheduler:	-1  t_create().  It should put processes on the
		   blocked queue.  New threads should be started with
		   t_ready(t_create(func)).
Tests:		-1  tg1 managed to lose some threads.
Misc:		-1  I had to compile it with the thread I wanted to run.

grade:	10/13
-------------

This one does not allow me to select which thread group I want to run.
It has to be compiled the way I want it to run.


This starts threads using t_create() only.  Does not do t_ready(t_create()).

Does not run tg2.

Will run tg1 and tg3.


tg1: missing 4 group1 threads.  missing 2 group2 threads.

tg3: ok


mmalloc()

	Static allocation of your memory:    memory[num_blocks * 64]
	would have given you much faster startup and this would have been
	more easily managed.


main()

	The lwp_yield(sched_id) does nothing for you.  The
	lwp_resume(sched_id) and exit(0) together will turn control over to
	the scheduler.  lwp_yield only works for threads at the same
	priority.


t_create()

	New threads should go on the "blocked" queue.  t_ready() will move
	them to the "ready" queue.


t_destroy()

	You should not rely on lwp primitives to tell you if the thread is
	dead.	Your OS should know this without consulting lwp.

b_get()

	Your semaphore is controlling the number of resources you can
	allocate, but it does not guarantee that you cannot have more than
	one process/thread updating your lists at the same time.



