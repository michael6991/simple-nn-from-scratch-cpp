/*
-----------------
 Introduction
-----------------
When dealing with arrays it’s often necessary to keep their elements in sorted order.
The easiest way is to use an insert algorithm that always puts element into the array in sorted order.

That said, you don’t know where elements will end up in the array because if you already knew the order
you wouldn’t need to sort in the first place.
At some point you will need to pull elements back out and you will want a quick way to find a given element.

Binary search and insert are great all around algorithms that do both of these.
It’s a simple divide and conquer approach that is conceptually vey simple. 
The array is divided into two parts and the search value is compared to to each part. One side is selected based on greater or less than. Then the side is divided and the comparison takes place again. This happens until the value is found or there are two values one above and one below (for insert).

Big-O complexity:

| | Best | Average | Worst | Time | O(1) | O(log n) | O(logn) | Space | | | O(n)

-----------------
Search
-----------------
While this is part of C89 and should be always be available it’s good to know how it works.
There is the off chance that you want to use a language that doesn’t have a built in binary search function.

*/

#include "binary_search.h"


// This variation ensures that if multiple elements match the first is found
void * binary_search(const void *base, size_t len, size_t width, const void *key, int (*cmp)(const void *, const void *))
{
	size_t mid = 0;
	size_t left;
	size_t right;
	int    eq  = -1;

	left  = 0;
	right = len;

	if (base == NULL || len == 0 || key == NULL || cmp == NULL)
		return NULL;

	while (left < right) {
		mid = (left + right) / 2;
		eq  = cmp(&key, base + (mid * width));
		if (eq < 0) {
			right = mid;
		} else if (eq > 0) {
			left = mid + 1;
		} else {
			break;
		}
	}

	if (eq != 0)
		return NULL;

	/* Return the first matching element */
	while (mid > 0 && mid >= left) {
		eq = cmp(&key, base+((mid - 1) * width));
		if (eq != 0) {
			break;
		}
		mid--;
	}

	return base + (mid * width);
}


/**
 * Insert is very similar to searching and can be integrated into one function with a search or insert flag.
 * I’m keeping them separate to keep the logic simple.
 * Insert is useful because you can insert into a sorted list and maintain proper sorting.
 * This way you don’t have to insert then run something like qsort on the list each and every time you put something in.
 * Actually, running a sorting algorithm after every insert is horribly inefficient.
 * If you can’t use an insert that algorithm that inserts in sorted order you should do a bulk insert and sort once at the end.
 * 
 * This only finds the insertion index and does not actually insert the data.
 * It’s up to the caller to handle shifting the data in the array to make room for the new element.
*/
size_t binary_insert(const void *base, size_t len, size_t width, const void *key, int (*cmp)(const void *, const void *))
{
	size_t mid = 0;
	size_t left;
	size_t right;
	int eq = 0;

	if (base == NULL || len == 0 || key == NULL || cmp == NULL)
		return 0;

	left  = 0;
	right = len;

	while (left < right) {
		mid = (left + right) / 2;
		eq  = cmp(&key, base + (mid * width));
		if (eq < 0) {
			right = mid;
		} else if (eq > 0) {
			left = mid + 1;
		} else {
			break;
		}
	}

	/* Insert after the index */
	if (eq > 0)
		mid++;

	/* Make the insert stable */
	while (mid < right && eq == 0) {
		mid++;
		eq = cmp(&key, base + (mid * width));
	}

	return mid;
}

// combination of search and insert
bool binary_search_and_insert(const void *base, size_t len, size_t width, const void *key, size_t *idx, bool is_insert, int (*cmp)(const void *, const void *))
{
    size_t mid = 0;
    size_t left;
    size_t right;
    int eq = -1;

    if (base == NULL || len == 0 || key == NULL || idx == NULL || cmp == NULL)
        return false;

    left  = 0;
    right = len;

    while (left < right) {
        mid = (left + right) / 2;
        eq  = cmp(&key, base + (mid * width));
        if (eq < 0) {
            right = mid;
        } else if (eq > 0) {
            left = mid + 1;
        } else {
            break;
        }
    }

    if (is_insert) {
        /* Insert after the index */
        if (eq > 0) {
            mid++;
        }

        /* Make the insert stable */
        while (mid < right && eq == 0) {
            mid++;
            eq = cmp(&key, base + (mid * width));
        }
    } else {
        if (eq != 0) {
            return false;
        }

        /* Return the first matching element */
        while (mid > 0 && mid >= left) {
            eq = cmp(&key, base + ((mid - 1) * width));
            if (eq != 0) {
                break;
            }
            mid--;
        }
    }

    *idx = mid;
    return true;
}
