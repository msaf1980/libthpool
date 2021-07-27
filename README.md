# Thread pool

# thpool_t (mutex-locked thread pool without allocation during task add)

This is a minimal threadpool implementation

  * ANCI C and POSIX compliant
  * Pause/resume/wait as you like

The threadpool is under MIT license.

## Basic usage

1. Include the header in your source file: `#include <thpool/thpool.h>
2. Create a thread pool with number of thpool you want: `threadpool pool = thpool_init(4, 1024);`
3. Add work to the pool: `thpool_add_task(pool, (void*)function_p, (void*)arg_p);`

The workers(thpool) will start their work automatically as fast as there is new work
in the pool. If you want to wait for all added work to be finished before continuing
you can use `thpool_wait(pool);`. If you want to destroy the pool you can use
`thpool_destroy(pool);`.


## API

For a deeper look into the documentation check in the [thpool.h](https://github.com/Pithikos/C-Thread-Pool/blob/master/thpool.h) file. Below is a fast practical overview.

| Function example                | Description                                                         |
|---------------------------------|---------------------------------------------------------------------|
| ***thpool_init(4, 1024)***            | Will return a new threadpool with `4` thpool and 1024 max queued (unproccessed) tasks.                        |
| ***thpool_workers_count(pool)*** | Will return count of workers thpool in thread poool               |
| ***thpool_add_task(pool, (void&#42;)function_p, (void&#42;)arg_p)*** | Will add new work to the pool. Work is simply a function. You can pass a single argument to the function if you wish. If not, `NULL` should be passed. |
| ***thpool_wait(pool)***       | Will wait for all jobs (both in queue and currently running) to finish. |
| ***thpool_destroy(pool)***    | This will destroy the threadpool. If jobs are currently being executed, then it will wait for them to finish. |
| ***thpool_pause(pool)***      | All thpool in the threadpool will pause no matter if they are idle or executing work. |
| ***thpool_resume(pool)***      | If the threadpool is paused, then all thpool will resume from where they were.   |
| ***thpool_active_tasks(pool)***  | Will return the number of active tasks (currently working thpool).   |
| ***thpool_total_tasks(pool)***  | Will return the number of tasks (queued and active).   |
| ***thpool_worker_try_once(pool)***  | Process task in current thread (foreground).   |
