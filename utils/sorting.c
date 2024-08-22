/*
-----------------
 Introduction
-----------------
Quicksort is most people’s go to sort function and that’s not a bad thing because it’s a really good general
purpose sorting algorithm.
A good implementation is really fast and, being an in place algorithm, it uses very little memory.

The big drawback of Quicksort is that it’s non-stable.
This means there are some situations where using Quicksort a deal breaker and can’t be used.
Here comes Mergesort which is stable.

That said, don’t think you should always use Mergesort instead of Quicksort.
Mergesort is slower and uses more memory.
A general rule of thumb is to use Quicksort unless you need a stable sort, then use Mergesort.

Big-O complexity:

| | Best | Average | Worst | Time | O(n log n) | O(n log n) | O(n log n) | Space | | | O(n)

*/
#include "sorting.h"


void merge_sort(void *base, size_t len, size_t width, int (*cmp)(const void *, const void *))
{
    char   *left;
    char   *right;
    size_t  ls;
    size_t  rs;
    size_t  mid;
    size_t  i;
    size_t  j;
    size_t  k;

    if (base == NULL || len < 2 || width == 0 || cmp == NULL)
        return;

    /* Find the mid and deal with an odd number of elements */
    mid = len / 2;
    ls  = mid;
    rs  = mid;

    if (len > 2 && len % 2 != 0)
        ls++;

    /* Copy the elements into tmp arrays */
    left  = malloc(ls * width);
    right = malloc(rs * width);
    memcpy(left, base, ls * width);
    memcpy(right, base + (ls * width), rs * width);

    merge_sort(left, ls, width, cmp);
    merge_sort(right, rs, width, cmp);

    i = 0;
    j = 0;
    k = 0;
    /* Merge the tmp arrays back into the base array in sorted order */
    while (i < ls && j < rs) {
        if (cmp(left + (i * width), right + (j * width)) <= 0) {
            memcpy(base + (k * width), left + (i * width), width);
            i++;
        } else {
            memcpy(base + (k * width), right + (j * width), width);
            j++;
        }
        k++;
    }

    /* If left is longer than right copy the remaining elements
     * over */
    while (i < ls) {
        memcpy(base + (k * width), left + (i * width), width);
        i++;
        k++;
    }

    /* If right is longer than right copy the remaining elements
     * over */
    while (j < rs) {
        memcpy(base + (k * width), right + (j * width), width);
        j++;
        k++;
    }

    free(right);
    free(left);
}
