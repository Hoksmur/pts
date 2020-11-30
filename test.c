#include <stdio.h>

#include "pts.h"


void task1(char ch)
{
	printf("Task 1 [%hhd]\n", ch );	
}


void task2( arg_t ch)
{
	printf("Task 2\n");	
}

void task3(arg_t vl)
{
	printf("Task 3 [%hhd]\n", vl );
	pts_set_to(task1, __LINE__);
	pts_set_to(task2, __LINE__);
	pts_set_to(task3, __LINE__); // Can not add to chain itself!
}



int main(int argc, char **argv)
{
	struct pts_task_desc *desc; 

	pts_task_init(task1, 2);
	pts_task_init(task2, 2);
	pts_task_init(task3, 0);
	desc = pts_get_desc(task2);
	printf(" Task2 descripror: %p, %hhu\n", desc->func, desc->stat);
	pts_run_chain();
	printf("Linear passed\n");
	pts_set_to(task2, __LINE__);
	pts_set_to(task1, __LINE__);
	pts_run_chain();
	printf("Inverse passed\n");
	pts_set_to(task3, __LINE__);
	pts_run_chain();
	printf("Call and self passed\n");
	pts_set_to(task1, __LINE__);
	pts_setmask_to(task1, 0x40);
	pts_run_chain();
	printf("Mask \'stat\' passed\n");

	return 0;
}

