#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include <thpool/thpool.h>

#include <ctest.h>

static void increment(void *p){
	int *n = (int *) p;
	__atomic_fetch_add(n, 1, __ATOMIC_RELAXED);
}

CTEST(thpool_pause_resume, test) {
	int num_thpool = 4;
	int i, jobs = 2;
	int n = 0;

	thpool_t pool = thpool_create(num_thpool, jobs);
	
	thpool_pause(pool);
	
	/* Since pool is paused, thpool should not start before main's sleep */
	for (i = 0; i < jobs; i++) {
		thpool_add_task(pool, increment, &n);
	}
	
	sleep(2);

	ASSERT_EQUAL_D(0, __atomic_load_n(&n, __ATOMIC_RELAXED), "thpool_pause not work");
	
	/* Now we will start thpool in no-parallel with main */
	thpool_resume(pool);

	sleep(2); /* Give some time to thpool to get the work */

	ASSERT_EQUAL_D(jobs, __atomic_load_n(&n, __ATOMIC_RELAXED), "thpool_resume not work");
	
	thpool_destroy(pool); // Wait for work to finish
}