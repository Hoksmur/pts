#include "pts.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

static bool again_fl = false;
#ifdef USE_TAB
 #ifdef TASK_ITEMS
 static pts_task_t tasks[ITEM_COUNT] = TASK_ITEMS;
 #else
 static pts_task_t tasks[ITEM_COUNT];
 #endif
#define TYPE short int
#define set_first(itm) itm = 0;
#define is_valid(itm)  (tasks[itm].func != NULL)
#define is_last(itm)   (itm >= ITEM_COUNT)
#define next(itm) itm++
#define task_fn(itm)  tasks[itm].func
#define task_st(itm)  tasks[itm].stat
#define ptr(itm)	&tasks[itm]
#define create(itm, F, S) if(itm <ITEM_COUNT) { task_fn(itm) = F, task_st(itm) = S; }

#else

static pts_task_t tasks[ITEM_COUNT];
#define TYPE pts_task_t *
#define set_first(itm) itm = &tasks[0] 
#define is_valid(itm)  (itm->func != NULL)
#define is_last(itm)   (NULL == itm->next)
#define next(itm)	itm = itm->next
#define task_fn(itm)   itm->func
#define task_st(itm)   itm->stat
#define ptr(itm)	itm
static void create( pts_task_t *last, void(*fn)(arg_t), arg_t st)
{
	short int i;
	for( i = 0; i < ITEM_COUNT; i++) {
		if( tasks[i].func == NULL ) {
			tasks[i].func = fn;
			tasks[i].stat = st;
			tasks[i].next = NULL;
			if(i != 0) { last->next = &tasks[i]; }
			break;
		}
	}
}

#endif

#if !defined(TASK_ITEMS)
void pts_task_init( void(*fn)(arg_t), arg_t st)
{
	TYPE set_first(item);
	while( is_valid(item) ) {
		if ( is_last(item) ) {
			break; 
		}
		next(item);
	}
	create(item, fn, st);
}
#endif

void pts_run_chain(void)
{
	TYPE set_first(item);
	while( is_valid(item) ) {
		if (task_st(item) != 0) {
			(task_fn(item))(task_st(item)); // Call function
			task_st(item) = 0; // Clear state when ran.
			if (again_fl) { // Rerun chain if any 'stat' changed 
				set_first(item);
				continue;
			};  
		}
		if ( is_last(item) ) { // if next isn't exist
			break;
		}
		next(item);
	}
}


void pts_set_to( void (*fn)(arg_t), arg_t st)
{
	TYPE set_first(item);
	while( task_fn(item) != fn) { 
		next(item);
		if ( is_last(item) ) {
			return;
		}
	}
	again_fl = true;
	task_st(item) = st;
}


pts_task_t *pts_get_desc( void (*fn)(arg_t) )
{
	TYPE set_first(item);
	while( task_fn(item) != fn) {
		next(item);
		if ( is_last(item) ) {
			return NULL;
		}
	}
	return ptr(item);
}

void pts_setmask_to( void (*fn)(arg_t), arg_t msk)
{
	TYPE set_first(item);
	while( task_fn(item) != fn) { // If not the same
		next(item);
		if ( is_last(item) ) {
			return;
		}
	}
	again_fl = true;
	task_st(item) |= msk;
}
