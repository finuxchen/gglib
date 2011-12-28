// gg_array.h - a dynamic array implement
//
// Finux Chen <fchen.cs@gmail.com>
//
// This file is part of gg_lib, which is designed to provide standard
// containers using C programming language.

#ifndef _GG_ARRAY_H
#define _GG_ARRAY_H

#include <unistd.h>

typedef void (*elem_func_t)(const char *args, ...);

typedef struct gg_array gg_array_t;

gg_array_t *gg_array_create(size_t array_size,
                            size_t elem_size,
                            elem_func_t construct_func,
                            elem_func_t destroy_func);

void gg_array_for_each(gg_array_t *array, elem_func_t func);

int gg_array_insert(gg_array_t *array, ssize_t pos, const void *elem);

int gg_array_ctor_insert(gg_array_t *array, ssize_t pos, ...);

int gg_array_delete(gg_array_t *array, ssize_t pos);

size_t gg_array_size(const gg_array_t *array);

void *gg_array_elem_at(const gg_array_t *array, size_t pos);

ssize_t gg_array_merge(gg_array_t *array, const gg_array_t *sub_array);

void gg_array_destroy(gg_array_t *array);


#endif // _GG_ARRAY_H
