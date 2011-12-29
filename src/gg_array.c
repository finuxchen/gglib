#include "gg_array.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdarg.h>

struct gg_array {
    void        *buffer;
    size_t      capability;
    size_t      size;
    size_t      elem_size;
    int         ctor_argc;
    elem_func_t c_func;
    elem_func_t d_func;
};

gg_array_t *gg_array_create(gg_array_elem_type_t elem_type, ...)
{
    gg_array_t *array = (gg_array_t *)malloc(sizeof(gg_array_t));
    if (array != NULL) {
        array->buffer       = NULL;
        array->capability   = 0;
        array->size         = 0;

        va_list arg_ptr;
        va_start(arg_ptr, elem_type);

        if (elem_type == GG_ARRAY_BASIC_TYPE) {
            array->elem_size    = va_arg(arg_ptr, size_t);
            array->ctor_argc    = 0;
            array->c_func       = NULL;
            array->d_func       = NULL;
        } else {
            array->elem_size    = 0;
            array->ctor_argc    = va_arg(arg_ptr, int);
            array->c_func       = va_arg(arg_ptr, elem_func_t);
            array->d_func       = va_arg(arg_ptr, elem_func_t);
        }

        va_end(arg_ptr);
    }

    return array;
}

size_t gg_array_size(const gg_array_t *thiz)
{
    return thiz->size;
}

size_t gg_array_capability(const gg_array_t *thiz)
{
    return thiz->capability;
}


int gg_array_insert(gg_array_t *thiz, ssize_t pos, ...)
{
//    assert(thiz != NULL && thiz->c_func != NULL);
    if (pos < -1 || pos > (ssize_t)thiz->size) {
        return -1;
    }
    
    if (thiz->elem_size != 0) {
        thiz->buffer = (void *)calloc(thiz->elem_size, 1);
    } else {
        thiz->buffer = (void *)calloc(sizeof(void *), 1);
        va_list arg_ptr;
        va_start(arg_ptr, pos);

        va_end(arg_ptr);
    }
}


void gg_array_destroy(gg_array_t *thiz)
{
    if (thiz != NULL) {
        // TODO: destroy buffer

        free(thiz);
    }
}

