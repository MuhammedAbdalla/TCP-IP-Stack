// /*
//     test_offset.c
// */
// #include "gluethread/glthread.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>

// #pragma pack(push,1)
// typedef struct emp_
// {
// 	char name[30];          // 0
// 	unsigned int salary;    // 30
// 	char designation[30];   // 34
// 	unsigned int empID;     // 64
//     glthread_node_t glnode; // x
// } emp_t;
// #pragma pack(pop)

// void print_emp_details(emp_t *data) {
//     printf("name\t\t%s\n",      data->name);
// 	printf("designation\t%s\n", data->designation);
// 	printf("ID\t\t%d\n",        data->empID);
// 	printf("salary\t\t%d\n",    data->salary);
// }

// int main(void)
// {
// 	emp_t e;
// 	printf("%ld\n", offsetof(emp_t, name));
// 	printf("%ld\n", offsetof(emp_t, salary));
// 	printf("%ld\n", offsetof(emp_t, designation));
// 	printf("%ld\n", offsetof(emp_t, empID));

//     emp_t *emp = calloc(1, sizeof(emp_t));
//     char *name = "Muhammed Abdalla";
//     char *designation = "BU ECE - Computer Engineer";

//     strncpy(emp->name, name, 30);
//     emp->name[30] = '\0';

//     strncpy(emp->designation, designation, 30);
//     emp->designation[30] = '\0';
    
//     emp->empID = 1;
//     emp->salary = 135000;

//     print_emp_details(emp);
// 	return 0;
// }