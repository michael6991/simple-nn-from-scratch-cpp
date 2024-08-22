/*
-----------------
 Introduction
-----------------
Lists (dynamic arrays) are yet another super useful data structure that C just doesn’t have.
C arrays are great for when you can get away with a fixed size but not so fun if you need to dynamically
expand because you don’t know quite how many elements you’ll need.
You could use a series of reallocs and memmoves but that’s going to get old really fast.

It’s also error prone and not obvious when growth is needed.
Not to mention you’ll end up with them all over the place.
The biggest issue I have with trying to manage a dynamic list manually is, it’s hard to track meta-data about the list.

For example, how many elements are in the list.
That’s pretty important if you ask me. One alternative to C arrays is a linked list. 
Not what I want because I want continues memory access and I don’t want the overhead of having a node per element.
Just like we created a generic hashtable, we can create a generic list using void pointers.

This generic container will leverages void pointers to allow holding any type of object.
We’ll make type safe wrappers around this generic container in order to get back the type safety we lost due to using void pointers.

-----------------
 Design
-----------------
We can’t get around the fact that C arrays are how we need to create a dynamic list but
we can abstract them so we don’t get into the mess of realloc and memmove.
Plus having one generic data type means we will have less error prone and easier to understand code.
Not to mention just like the generic hashtable, we can wrap it for type safety.

*/
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "binary_search.h"
#include "sorting.h"


// block size that represents the size of an element/some generic object/item
static const size_t list_block_size = 32;


// list object
struct list {
    void         **elements;
    size_t          alloced;
    size_t          len;
    list_cbs_t      cbs;
    list_flags_t    flags;
    bool            inbulk;
};


/**
 * equality function to compare objects. the list is a generic container
 * and can hold any kind of object.
 * function compares the pointer address of each object in the array.
*/
static int list_passthrough_eq(const void *a, const void *b)
{
    void *sa = *(void **)a;
    void *sb = *(void **)b;

    return sa - sb;
}


list_t *list_create(const list_cbs_t *cbs, list_flags_t flags)
{
    list_t *l;

    /* basic initialization */
    l           = malloc(sizeof(*l));
    l->elements = malloc(sizeof(*l->elements) * list_block_size);
    l->alloced  = list_block_size;
    l->len      = 0;

    /* acquire the appropriate list callbacks */
    memset(&(l->cbs), 0, sizeof(l->cbs));
    if (cbs != NULL) {
        l->cbs.leq   = cbs->leq;
        l->cbs.lcopy = cbs->lcopy;
        l->cbs.lfree = cbs->lfree;
    }
    if (l->cbs.leq == NULL)
        l->cbs.leq = list_passthrough_eq;

    l->flags = flags;

    return l;
}


void list_destroy(list_t *l)
{
    size_t i;

    if (l == NULL)
        return;

    /* iterate on the elements and destroy each one */
    if (l->cbs.lfree != NULL) {
        for (i=0; i < l->len; i++) {
            l->cbs.lfree(l->elements[i]);
        }
    }

    free(l->elements);
    free(l);
}


size_t list_len(list_t *l)
{
    if (l == NULL)
        return 0;
    return l->len;
}


/**
 * there are two parts to insertion.
 * with sorting enabled and with sorting disabled.
 * where items are inserted differs between these two modes.
 * when sorted, the insertion index will be found using the equality function against items currently in the list.
 * whereas, unsorted the insert will happen at the given index.
 * 
 * this is stable, meaning if there are matching values insert will always return
 * the index after the last one.
*/

// insert puts the object at the end when unsorted
bool list_insert(list_t *l, void *v, size_t idx)
{
    if (l == NULL || v == NULL)
        return false;

    // ran out of space, list need to grow
    if (l->alloced == l->len) {
        l->alloced += list_block_size;
        l->elements = realloc(l->elements, sizeof(*l->elements)*l->alloced);
        // multiply by size of void * pointer! (8 bytes on 64-machines, 4 bytes on 32-bit machines)
    }

    // if necessary, copy the new element v into the the list
    if (l->cbs.lcopy != NULL)
        v = l->cbs.lcopy(v);

    // if sorted list, first determine the index of insertion
    if (l->flags & LIST_SORT && !l->inbulk)
        binary_search(l->elements, l->len, sizeof(*l->elements), v, l->cbs.leq);

    if (idx > l->len) {
        idx = l->len;
    } else if (idx < l->len) {
        memmove(l->elements + (idx + 1), l->elements + idx, (l->len - idx) * sizeof(*l->elements));
    }
    l->elements[idx] = v;

    l->len++;
    return true;
}


// for a sorted list, append will do exactly the same as insert
bool list_append(list_t *l, void *v)
{
    if (l == NULL || v == NULL)
        return false;
    return list_insert(l, v, l->len);
}


static bool list_remove_int(list_t *l, size_t idx, bool do_free)
{
    if (l == NULL || idx >= l->len)
        return false;

    if (do_free && l->cbs.lfree != NULL)
        l->cbs.lfree(l->elements[idx]);

    l->len--;
    if (idx == l->len)
        return true;

    memmove(l->elements+idx, l->elements+(idx+1), (l->len-idx)*sizeof(*l->elements));
    return true;
}


bool list_remove(list_t *l, size_t idx)
{
    return list_remove_int(l, idx, true);
}


/**
 * binary search is used only for a sorted list. O(log n)
 * linear search is used for un-sorted list. O(n)
*/
bool list_index_of(list_t *l, void *v, size_t *idx)
{
    size_t i;

    if (l == NULL || v == NULL)
        return false;

    if (l->flags & LIST_SORT && !l->inbulk) {
        idx = binary_search(l->elements, l->len, sizeof(*l->elements), v, l->cbs.leq);
        if (idx != NULL) {
            return true;
        }
        return false;
    }

    for (i=0; i < l->len; i++) {
        if (l->cbs.leq(&v, &l->elements[i]) == 0) {
            *idx = i;
            return true;
        }
    }
        
    return false;
}


/**
 * return the element but keep it in the list. we actually return an address.
 * you CANNOT!!! destroy the element while it's still in the list.
 * that can cause un-expected behaviour and crash.
*/ 
void * list_get(list_t *l, size_t idx)
{
    if (l == NULL || idx >= l->len)
        return NULL;
    return l->elements[idx];
}


/**
 * like get, it returns the object but unlike get,
 * it removes it from the list.
 * that’s why we made the internal remove_int function above.
*/
void *list_take(list_t *l, size_t idx)
{
    void *out;

    if (l == NULL || idx >= l->len)
        return NULL;

    out = list_get(l, idx);
    list_remove_int(l, idx, false);
    return out;
}


// e is a comparison function that can be applied on the elements of the list.
bool list_sort(list_t *l, list_eq e)
{
    if (l == NULL)
        return false;

    if (l->flags & LIST_SORT) {
        if (e != NULL) {
            l->cbs.leq = e;
        } else {
            e = l->cbs.leq;
        }
    }

    if (e == NULL)
        return false;

    // stable sorting method. has a memory penalty for large lists though,
    // so keep in mind.
    mergesort(l->elements, l->len, sizeof(*l->elements), e);
}


/**
 * these just set the inbulk flag so other functions know
 * if they should skip sorting.
 * when we’ve finished bulk adding we’ll just sort the list.
*/
void list_start_bulk_add(list_t *l)
{
    if (l == NULL)
        return;
    l->inbulk = true;
}

void list_end_bulk_add(list_t *l)
{
    if (l == NULL)
        return;
    l->inbulk = false;
    list_sort(l, NULL);
}
