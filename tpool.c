/*
-----------------
 Introduction
-----------------
Creating threads can be quite expensive.
Typically each thread is going to do essentially the same thing so it’s good to keep reusing them.

Threads are actually quite heavy and creating or destroying threads takes time away from what you’re trying to accomplish.
Another benefit of thread pools is that they keep the system from becoming overloaded.
They allow a limit to the number of threads. Tasks are queued and only run when a thread is available.

-----------------
 Design
-----------------
Th thread pool keeps a set number of threads running and waiting to do something.
The pool could be designed to scale up with the amount of work you need to do.
I prefer specifying a fixed number of threads.
A good way to choose this number is to use the number of cores/processors on the system + 1.

At the heart of a thread pool are threads. I’m using pthreads.

-----------------
Further Work
-----------------
This implementation uses a linked list so it can queue an infinite amount of work.
Another option would be to set a fixed size queue and have tpool_add_work block if there are no open slots.
If you’re worried about memory usage you should think about this.
*/
#include "tpool.h"


struct tpool_work {
    thread_func_t      func;
    void              *arg;
    struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;


/** 
* Work queue is implemented as a linked list.
* Work_first and work_last are used to push and pop work objects.
* There is a single mutex (work_mutex) which is used for all locking.
*
* We need two conditionals, work_cond signals the threads that there is work
* to be processed and working_cond signals when there are no threads processing.
* We combine these with working_cnt to know how many threads are actively processing work.
* We’re not checking if the threads running because they’ll always be running as part of the pool.
* They’re just not using resources if they’re not processing any work.
*
* Finally, we track how many threads are alive using thread_cnt.
* This helps us prevent running threads from being destroyed prematurely.
* This is used in conjunction with stop which actually stops the threads.
*/
struct tpool {
    tpool_work_t    *work_first;
    tpool_work_t    *work_last;
    pthread_mutex_t  work_mutex;
    pthread_cond_t   work_cond;
    pthread_cond_t   working_cond;
    size_t           working_cnt;
    size_t           thread_cnt;
    bool             stop;
};


// Simple helpers for creating and destroying work objects.
static tpool_work_t *tpool_work_create(thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if (func == NULL)
        return NULL;

    work       = malloc(sizeof(*work));
    work->func = func;
    work->arg  = arg;
    work->next = NULL;
    return work;
}

static void tpool_work_destroy(tpool_work_t *work)
{
    if (work == NULL)
        return;
    free(work);
}


/**
 * Work will need to be pulled from the queue at some point to be processed.
 * Since the queue is a linked list this handles not only pulling an object
 * from the list but also maintaining the list work_first and work_last references for us.
*/
static tpool_work_t *tpool_work_get(tpool_t *tm)
{
    tpool_work_t *work;

    if (tm == NULL)
        return NULL;

    work = tm->work_first;
    if (work == NULL)
        return NULL;

    if (work->next == NULL) {
        tm->work_first = NULL;
        tm->work_last  = NULL;
    } else {
        tm->work_first = work->next;
    }

    return work;
}


/**
 * This is the heart and soul of the pool and is where work is handled.
 * At a high level this waits for work and processes it.
*/
static void *tpool_worker(void *arg)
{
    tpool_t      *tm = arg;
    tpool_work_t *work;

    // This will keep the tread running and as long as it doesn’t exit it can be used
    while (1) {
        // The first thing that happens is locking the mutex
        // so we can be sure nothing else manipulates the pool’s members
        pthread_mutex_lock(&(tm->work_mutex));

        // Check if there is any work available for processing and we are still running
        // We’ll wait in a conditional until we’re signaled and run our check again.
        while (tm->work_first == NULL && !tm->stop)
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));

        // Now we check if the pool has requested that all threads stop running and exit
        // The stop check is all the way up here because we want to stop before pulling any work.
        // The mutex will be unlocked before the thread exists.
        if (tm->stop)
            break;

        // Once the thread was signaled there is work, we’ll pull some from the queue
        // and increment working_cnt so the pool knows a thread is processing.
        // The mutex is unlocked so other threads can pull and process work.
        // We want the work processing to happen in parallel it doesn’t make sense
        // to hold the lock while work is processing.
        // The lock is only there to synchronize pulling work from the queue.
        work = tpool_work_get(tm);
        tm->working_cnt++;
        pthread_mutex_unlock(&(tm->work_mutex));

        // If there was work, process it and destroy the work object.
        // It is possible that there was no work at this point
        // so there isn’t anything that needs to be done.
        if (work != NULL) {
            work->func(work->arg);
            tpool_work_destroy(work);
        }

        // Finally, once the work has been processed (or not if there wasn’t any)
        // the mutex will be locked again and working_cnt is decreased because the work is done.
        pthread_mutex_lock(&(tm->work_mutex));
        tm->working_cnt--;

        // If there are no threads working and there are no items in the queue a signal
        // will be sent to inform the wait function (in case someone’s waiting) to wake up.
        if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
            pthread_cond_signal(&(tm->working_cond));
        pthread_mutex_unlock(&(tm->work_mutex));
    }

    // Since we know that only one thread can hold the lock,
    // then only the last thread to finish it’s work can decrement working_cnt to zero.
    // This way we know there aren’t any threads working.
    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return NULL;
    // Notes:
    // At the top of the run loop we break out on stop and this is where it leads us.
    // We decrement the thread count because this thread is stopping.

    // Then we signal tpool_wait that a thread has exited.
    // We need to do this here because tpool_wait will wait for all threads to exit when stopping.
    // If we’re here it’s because tpool_destroy was called and it’s waiting for tpool_wait to exit.
    // Once all threads have exited tpool_wait will return allowing tpool_destroy to finish.

    // We unlock the mutex last because everything is protected by it, and we’re guaranteed
    // tpool_wait won’t wake up before the thread finishes it’s cleanup. The signal above only runs after we unlock.
}


/**
 * When creating the pool the default is two threads if zero was specified.
 * Otherwise, the caller specified number will be used.
 * It’s a good idea for us to have a default but two might be a little low.
 * This goes back to the idea of using the number of core/processors + 1 as the default.
 * 
 * Note:
 * There is no need to store the thread ids because they will never be accessed directly.
 * If we wanted to implement some kind of force exit instead of having to wait then we’d need to track the ids.
*/
tpool_t *tpool_create(size_t num)
{
    tpool_t   *tm;
    pthread_t  thread;
    size_t     i;

    if (num == 0)
        num = 2;

    tm             = calloc(1, sizeof(*tm));
    tm->thread_cnt = num;

    pthread_mutex_init(&(tm->work_mutex), NULL);
    pthread_cond_init(&(tm->work_cond), NULL);
    pthread_cond_init(&(tm->working_cond), NULL);

    tm->work_first = NULL;
    tm->work_last  = NULL;

    for (i=0; i < num; i++) {
        // tpool_worker is specified as the thread function
        pthread_create(&thread, NULL, tpool_worker, tm);
        pthread_detach(thread);
    }

    return tm;
}


/**
 * Once all outstanding processing finishes the pool object is destroyed. 
 * Typically, destroy will only be called when all work is done and nothing is processing.
 * However, it’s possible someone is trying to force processing to stop.
 * In which case there will be work queued and we need to get clean it up.
*/
void tpool_destroy(tpool_t *tm)
{
    tpool_work_t *work;
    tpool_work_t *work2;

    if (tm == NULL)
        return;

    // We are throwing away all pending work but  the caller really should
    // have dealt with this situation since they’re the one that called destroy.
    // This won’t interfere with anything currently processing
    // because the threads have pulled off the work they’re working on.
    pthread_mutex_lock(&(tm->work_mutex));
    work = tm->work_first;
    while (work != NULL) {
        work2 = work->next;
        tpool_work_destroy(work);
        work = work2;
    }

    // Once we’ve cleaned up the queue we’ll tell the threads they need to stop.
    tm->work_first = NULL;
    tm->stop = true;
    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));

    // Some threads may have already been running
    // and are currently processing so we need to wait for them to finish.
    // Note:
    // This is where a force exit parameter could be implemented 
    // which would kill all threads instead of waiting on them to finish.
    // (We must be carefull with this idea)
    tpool_wait(tm);

    pthread_mutex_destroy(&(tm->work_mutex));
    pthread_cond_destroy(&(tm->work_cond));
    pthread_cond_destroy(&(tm->working_cond));

    free(tm);
}


/**
 * Adding to the work queue consists of creating a work object,
 * locking the mutex and adding the object to the liked list
*/
bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if (tm == NULL)
        return false;

    work = tpool_work_create(func, arg);
    if (work == NULL)
        return false;

    pthread_mutex_lock(&(tm->work_mutex));
    if (tm->work_first == NULL) {
        tm->work_first = work;
        tm->work_last  = tm->work_first;
    } else {
        tm->work_last->next = work;
        tm->work_last       = work;
    }

    pthread_cond_broadcast(&(tm->work_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
    return true;
}


/**
 * This is a blocking function that will only return when there is no work.
 * The mutex is locked and we wait in a conditional if there are any threads processing,
 * or if there's still work to do, or if the threads are stopping and not all have exited.
 * The retry is a safety measure in case of spurious wake ups.
 * Once there's nothing processing, return so the caller can continue.
*/
void tpool_wait(tpool_t *tm)
{
    if (tm == NULL)
        return;

    pthread_mutex_lock(&(tm->work_mutex));
    while (1) {
        if (tm->work_first != NULL || (!tm->stop && tm->working_cnt != 0) || (tm->stop && tm->thread_cnt != 0)) {
            pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
        } else {
            break;
        }
    }
    pthread_mutex_unlock(&(tm->work_mutex));
}

