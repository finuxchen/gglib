#include "gg_array.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdarg.h>

struct gg_array {
    void        *buffer;
    size_t      allocated_size;
    size_t      size;
    size_t      elem_size;
    elem_func_t c_func;
    elem_func_t d_func;
};

static void *insert_move(gg_array_t *array, ssize_t pos);


gg_array_t *gg_array_create(size_t array_size,
                            size_t elem_size,
                            elem_func_t construct_func,
                            elem_func_t destroy_func)
{
    // array size and element size SHOULD NOT be 0!
    if (array_size == 0 || elem_size == 0) {
        return NULL;
    }

    gg_array_t *new_array = (gg_array_t *)malloc(sizeof(gg_array_t));
    if (new_array != NULL) {
        new_array->allocated_size   = array_size;
        new_array->size             = 0;
        new_array->elem_size        = elem_size;
        new_array->c_func           = construct_func;
        new_array->d_func           = destroy_func;
        new_array->buffer           = calloc(elem_size, array_size);

        // if buffer allocate failed, free memory 
        if (new_array->buffer == NULL) {
            free(new_array);
            return NULL;
        }

        // if allocate success, construct all elements
//        if (construct_func != NULL) {
//            gg_array_for_each(new_array, construct_func);
//        }
    }

    return new_array;
}

void gg_array_for_each(gg_array_t *array, elem_func_t func)
{
    for (int pos = 0; pos < array->size; ++pos) {
        func(array->buffer + array->elem_size * pos);
    }
}

int gg_array_insert(gg_array_t *array, ssize_t pos, const void *elem)
{
    void *elem_ptr = insert_move(array, pos);
    if (elem_ptr == NULL) {
        return -1;
    }
    memcpy(elem_ptr, elem, array->elem_size);

    return array->size;
}

int gg_array_ctor_insert(gg_array_t *array, ssize_t pos, ...)
{
    void *elem_ptr = insert_move(array, pos);
    if (elem_ptr == NULL) {
        return -1;
    }



    return array->size;
}

int gg_array_delete(gg_array_t *array, ssize_t pos)
{
    // make sure the pos is in valid range
    if (pos < -1 || pos > (ssize_t)(array->size - 1)) {
        return -1;
    }

    // when pos == -1, delete the tail element
    size_t op_pos = pos == -1 ? array->size - 1 : pos;

    // move all elements after the delete position backward one step      
    for (int curr_pos = op_pos + 1; curr_pos < array->size; ++curr_pos) {
        memcpy(array->buffer + (curr_pos - 1) * array->elem_size,
               array->buffer + curr_pos * array->elem_size,
               array->elem_size);
    }

    // destroy the element at the tail
    if (array->d_func != NULL) {
        array->d_func(array->buffer + (array->size - 1) * array->elem_size);
    }
    memset(array->buffer + (array->size - 1) * array->elem_size, 0, array->elem_size);
    --array->size;

    return 0;
}

size_t gg_array_size(const gg_array_t *array)
{
    return array->size;
}


void *gg_array_elem_at(const gg_array_t *array, size_t pos)
{
    if (pos > array->size - 1) {
        return NULL;
    }
    return (array->buffer + pos * array->elem_size);
}

// TODO:
ssize_t gg_array_merge(gg_array_t *array, const gg_array_t *sub_array)
{
    // if allocated size of array is not enough, realloc memory
    size_t total_size = array->size + sub_array->size;
    if (total_size > array->allocated_size) {
        void *new_buffer = realloc(array->buffer,
                                   total_size * array->elem_size);
        if (new_buffer == NULL) {
            return -1;
        }
        array->buffer           = new_buffer;
        array->allocated_size   = total_size;
        array->size             = total_size;
    }

    // copy sub_array elements to array


    return -1;
}

// TODO:
//ssize_t gg_array_merge(
//        gg_array_t *array, const void *sub_array, size_t sub_size)
//{
//    return -1;
//}

void gg_array_destroy(gg_array_t *array)
{
    if (array->d_func != NULL) {
        gg_array_for_each(array, array->d_func);
    }
    free(array->buffer);
    free(array);
}



// ----------------------------------------------------------------------------
// static functions
// ----------------------------------------------------------------------------


void *insert_move(gg_array_t *array, ssize_t pos)
{
    // make sure the pos is in valid range
    if (pos < -1 || pos > (ssize_t)array->size) {
        return NULL;
    }

    // when pos == -1, insert at position next to the tail element
    size_t op_pos = pos == -1 ? array->size : pos;

    // buffer full, realloc memory (double memory)
    if (array->size == array->allocated_size) {
        void *new_buffer = realloc(array->buffer,
                                  (array->allocated_size * 2) * array->elem_size);
        if (new_buffer == NULL) {
            return NULL;
        }
        array->buffer = new_buffer;
        array->allocated_size *= 2;
    }

    // move all elements after the insert position forward one step
    for (int curr_pos = array->size; curr_pos > op_pos; --curr_pos) {
        memcpy(array->buffer + curr_pos * array->elem_size, 
               array->buffer + (curr_pos - 1) * array->elem_size,
               array->elem_size);
    }
    ++array->size;

    return (array->buffer + op_pos * array->elem_size);
}
