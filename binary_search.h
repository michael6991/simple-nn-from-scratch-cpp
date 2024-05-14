#ifndef __BINSEARACH_H__
#define __BINSEARACH_H__

#include <stdlib.h>
#include <stdbool.h>


void * binary_search(const void *base, size_t len, size_t width, const void *key, int (*cmp)(const void *, const void *));
size_t binary_insert(const void *base, size_t len, size_t width, const void *key, int (*cmp)(const void *, const void *));
bool binary_search_and_insert(const void *base, size_t len, size_t width, const void *key, size_t *idx, bool is_insert, int (*cmp)(const void *, const void *));

#endif /* __LIST_H__ */