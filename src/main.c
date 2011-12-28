#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "gg_array.h"

void print_double(void *d)
{
    printf("%f\n", *((double *)d));
}

void print_array(const gg_array_t *array)
{
    printf("array size = %d, all elements are:\n", gg_array_size(array));
    gg_array_for_each((gg_array_t *)array, print_double);
}

typedef struct student {
    unsigned int id;
    char name[10];
} student_t;

void student_c_func(void *s)
{
    student_t *stu = (student_t *)s;
    stu->id = 1;
    strcpy(stu->name, "xiaog");
}

void student_d_func(void *s)
{
    student_t *stu = (student_t *)s;
    stu->id = 0;
    memset(stu->name, 0, 10);
}

void print_student(void *s)
{
    student_t *stu = (student_t *)s;
    printf("student id is %d, name is %s\n", stu->id, stu->name);
}

int main(int argc, char **argv)
{
    printf("double array test ####\n");
    gg_array_t *p = gg_array_create(10, sizeof(double), NULL, NULL);
    double d1 = 1.024;
    double d2 = 2.024;
    gg_array_insert(p, 0, &d1);
    gg_array_insert(p, -1, &d2);
    printf("elem at 0 is %f\n", *((double *)gg_array_elem_at(p, 0)));
    print_array(p);
    gg_array_delete(p, -1);
    print_array(p);
    printf("double array test end ####\n");

//    printf("struct array test ####\n");
//    gg_array_t *ps = gg_array_create(10, sizeof(student_t), student_c_func, student_d_func);
//    student_t stu = { 100, "xiaog" };
//    gg_array_insert(ps, -1, &stu);
//    gg_array_for_each(ps, print_student);
//    printf("struct array test end ####\n");

    return 0;
}
