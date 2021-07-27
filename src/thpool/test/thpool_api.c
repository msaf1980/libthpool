#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>

#include <thpool/thpool.h>

#include <ctest.h>

static void sleep_job(void *p){
	int *n = (int *) p;
	__atomic_add_fetch(n, 1, __ATOMIC_RELEASE);
	puts("SLEPT");
}


CTEST(thpool_api, test) {
	thpool_t pool;
	int n;

	/* Test if we can get the current number of working thpool */
	n = 0;
	pool = thpool_create(10, 10);
	thpool_add_task(pool, sleep_job, &n);
	thpool_add_task(pool, sleep_job, &n);
	thpool_add_task(pool, sleep_job, &n);
	thpool_add_task(pool, sleep_job, &n);
	
	thpool_wait(pool);

	ASSERT_EQUAL(0, thpool_active_tasks(pool));
	ASSERT_EQUAL(0, thpool_total_tasks(pool));
	ASSERT_EQUAL(4, __atomic_add_fetch(&n, 0, __ATOMIC_RELEASE));

	thpool_destroy(pool);

	/* Test (same as above) */
	n  = 0;
	pool = thpool_create(5, 5);
	thpool_add_task(pool, sleep_job, &n);
	thpool_add_task(pool, sleep_job, &n);

	thpool_wait(pool);

	ASSERT_EQUAL(0, thpool_active_tasks(pool));
	ASSERT_EQUAL(0, thpool_total_tasks(pool));
	ASSERT_EQUAL(2, __atomic_add_fetch(&n, 0, __ATOMIC_RELEASE));

	thpool_destroy(pool);
}
