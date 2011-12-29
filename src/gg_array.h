#ifndef _GG_ARRAY_H
#define _GG_ARRAY_H

#include <unistd.h>

typedef enum {
   GG_ARRAY_BASIC_TYPE = 0,
   GG_ARRAY_STRUCT
} gg_array_elem_type_t;

typedef void *(*elem_func_t)(void *, ...);

typedef struct gg_array gg_array_t;

gg_array_t *gg_array_create(gg_array_elem_type_t elem_type, ...);

inline size_t gg_array_size(const gg_array_t *thiz);

inline size_t gg_array_capability(const gg_array_t *thiz);

int gg_array_insert(gg_array_t *thiz, ssize_t pos, void *arg1, ...);

void gg_array_destroy(gg_array_t *thiz);

#endif // _GG_ARRAY_H
