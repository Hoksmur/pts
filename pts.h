#ifndef __PTS_H__
#define __PTS_H__

#define arg_t char
/* Other varants: */
// typedef char arg_t;
// typedef int  arg_t;

/* Coment USE_TAB if you want to use linked list.
 * But descriptors stored it tab yet. For dynamically 
 * allocate implement your own create() function. */
#define USE_TAB
#define ITEM_COUNT 4

/* Structure describes task, has status
 * and [ pointer to next task | nillptr ] */
typedef struct pts_task_desc_st {
	arg_t stat;
	void (*func)(arg_t);
#ifndef USE_TAB
	struct pts_task_desc_st *next;
#endif	
} pts_task_t;


/* Add task to chain, where it can ran */
/* For USE_TAB you can define TASK_ITEMS *
 * to initialize tasks with compound literals
 * and disable pts_task_init() function. */
void pts_task_init( void (*fn)(arg_t), arg_t st);

/* Run chain once. If you need loop wrap it on for(;;) or while(1) 
 * Also chain will not ends if tasks will call each other. */
void pts_run_chain(void);

/* Set state for task (by name). */
void pts_set_to( void (*fn)(arg_t), arg_t st);

/* Return pointer to task's descriptor. 
 * Can be usefull for fast stat's set and call when lot of tasks in list.
 * But for call need initialize it earlier.
 * (for itself pts_set_to() hasn't effect).
 */
pts_task_t *pts_get_desc( void (*fn)(arg_t) );

/* Set state|mask for task (by name). *
 * Usefull for few sources to activate task
 */
void pts_setmask_to( void (*fn)(arg_t), arg_t msk);

#endif /* __PTS_H__ */
