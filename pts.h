#pragma once

#include <stdint.h>

#define arg_t char
// Other varant:
// typedef char arg_t;
// typedef int  arg_t;


/* Structure describes task, has status
 * and pointer to next task (or nillptr) */
struct pts_task_desc {
	arg_t stat;
	struct pts_task_desc *next;
	void (*func)(arg_t);
};

/* Add task to chain, where it can ran */
void pts_task_init( void (*fn)(arg_t), arg_t st);

/* Run chain once. If you need loop wrap it on for(;;) or while(1) 
 * Also chain will not ends if tasks will call each other */
void pts_run_chain(void);

/* Set state for task (by name). */
void pts_set_to( void (*fn)(arg_t), arg_t st);


/* Return pointer to task's descriptor. 
 * Can be usefull for fast stat's set and call when lot of tasks in list.
 * But for call need run pts_set_to() before.
 * (for itself, usually it has not effect).
 */
struct pts_task_desc *pts_get_desc( void (*fn)(arg_t) );

/* Set state|mask for task (by name). */
void pts_setmask_to( void (*fn)(arg_t), arg_t msk);
