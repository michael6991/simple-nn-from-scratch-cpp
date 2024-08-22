#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "list.h"
#include "htable.h"
#include "sorting.h"
#include "binary_search.h"
#include "tpool.h"


static const size_t num_threads = 4;
static const size_t num_items   = 100;

void worker(void *arg)
{
    int *val = arg;
    int  old = *val;

    *val += 1000;
    printf("tid=%p, old=%d, val=%d\n", pthread_self(), old, *val);

    if (*val % 2)
        usleep(100000);
}


int cmp_int(const void * a, const void * b)
{
    return ( *(int *)a - *(int *)b );
}


int main(int argc, char **argv)
{
    printf("%s:%s:%d \n", __FILE__, __FUNCTION__, __LINE__);
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
    printf("[!] Testing sorting: merge_sort\n");
    int a[17] = {0};
    int i;
    bool is_passed = true;

    srand(time(NULL));
    for (i=0; i < 17; i++) {
        a[i] = (rand() % 100) * ((rand() % 2) ? 1: -1); // [-99, +99]
    }

    printf("[*] Input:  [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
    a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16]);

    merge_sort(a, 17, sizeof(int), cmp_int);

    printf("[*] Output: [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
    a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15],a[16]);

    for (i=0; i < 16; i++) {
        if (a[i] > a[i + 1]) {
            is_passed = false;
            break;
        }
    }
    printf("[!] Finished sorting test with result: [%s]\n\n", is_passed ? "PASSED": "FAILED");
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

    printf("[!] Testing thread pool: 4 threads and 100 work items\n");
    tpool_t *tm;
    int     *vals;

    is_passed = false;
    tm   = tpool_create(num_threads);
    vals = calloc(num_items, sizeof(*vals));

    for (i=0; i<num_items; i++) {
        vals[i] = i;
        tpool_add_work(tm, worker, vals+i);
    }

    tpool_wait(tm);

    for (i=0; i < num_items; i++) {
        printf("%d\n", vals[i]);
    }

    if (vals[num_items-1] == 1099) {
        is_passed = true;
    }
    free(vals);
    tpool_destroy(tm);
    
    printf("[!] Finished thread pool test with result: [%s]\n\n", is_passed ? "PASSED": "FAILED");

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

    // printf("Testing generic list\n");


    return 0;
}