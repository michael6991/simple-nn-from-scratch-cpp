#ifndef __SORTING_H__
#define __SORTING_H__

#include <stdlib.h>
#include <string.h>

void merge_sort(void *base, size_t len, size_t width, int (*cmp)(const void *, const void *));

#endif /* __SORTING_H__ */