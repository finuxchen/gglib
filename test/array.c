#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "gg_array.h"

typedef struct stu_s {
    unsigned int    id;
    const char      *name;
} stu_t;

stu_t *stu_ctor(unsigned int id, const char *name)
{
    stu_t *stu = (stu_t *)malloc(sizeof(stu_t));
    if (stu != NULL) {
        stu->id = 100;
        stu->name = "xiaog";
    }
    return stu;
}

int main(int argc, char **argv)
{

    return 0;
}
