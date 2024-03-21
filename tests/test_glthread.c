/*
    test_glthreads.c
*/

#include "gluethread/glthread.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct emp_ emp_t;

struct emp_ {
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_node_t glnode;
};


void print_emp_details(emp_t *emp) {
    printf("Employee     \t%s\n", emp->name);
    printf("Salary       \t%d\n", emp->salary);
    printf("Designation  \t%s\n", emp->designation);
    printf("Employee id  \t%d\n", emp->emp_id);
}


int main(int argc, char **argv) {
    /* create gl thread */
    glthread_t *emp_list = calloc(1, sizeof(glthread_t));
    init_glthread(emp_list, offsetof(emp_t, glnode));


    emp_t *emp1 = calloc(1, sizeof(emp_t));
    strncpy(emp1->name,"Muhammed",strlen("Muhammed"));
    emp1->salary = 80000;
    strncpy(emp1->designation,"SWE", strlen("SWE"));
    emp1->emp_id = -1;
    glthread_node_init((&emp1->glnode));

    /* insert records */
    glthread_add(emp_list, &emp1->glnode);

    for (int i = 0; i < 30; i++) {
        emp1 = calloc(1, sizeof(emp_t));
        strncpy(emp1->name,"Muhammed",strlen("Muhammed"));
        emp1->salary = i*1000;
        strncpy(emp1->designation,"SWE", strlen("SWE"));
        emp1->emp_id = i;
        glthread_node_init((&emp1->glnode));
        glthread_add(emp_list, &emp1->glnode);
    }

    /* walk over glthread */
    emp_t *ptr = NULL;
    ITERATE_GLTHREADS_BEGIN(emp_list, emp_t, ptr){
        printf("\n");
        print_emp_details(ptr);
    } ITERATE_GLTHREADS_ENDS;

    free(emp_list);
    return 0;
}