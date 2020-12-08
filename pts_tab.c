#include "pts.h"
#include <stdbool.h>
// ONLY TAB implementation
// for readable code.

static bool again_fl = false;
#ifdef USE_TAB
 #ifdef TASK_ITEMS
 static pts_task_t tasks[ITEM_COUNT] = TASK_ITEMS;
 #else
 static pts_task_t tasks[ITEM_COUNT];
 #endif
#else
 #error Tab only in this file
#endif

void pts_task_init( void(*fn)(arg_t), arg_t st)
{
	short int num = 0; // Set first item.
	while( (tasks[num].func != NULL) && (num <= ITEM_COUNT) ) {
		++num;
	}
	tasks[num].func = fn;
	tasks[num].stat = st;
}


void pts_run_chain(void)
{
	short int num = 0;
	while( tasks[num].func != 0 ) {
		if (tasks[num].stat != 0) {
			(tasks[num].func)(tasks[num].stat);
			tasks[num].stat = 0; // Clear state when ran.
			if (again_fl) { // Rerun chain if any 'stat' changed 
				num = 0;
				continue;
			};  
		}
		if ( ++num >= ITEM_COUNT ) { // if next isn't exist
			break;
		}
	}
}


void pts_set_to( void (*fn)(arg_t), arg_t st)
{
	short int num = 0;
	while( tasks[num].func != fn) { // if not required
		if ( ++num >= ITEM_COUNT ) {
			return;
		}
	}
	again_fl = true;
	tasks[num].stat = st;
}


pts_task_t *pts_get_desc( void (*fn)(arg_t) )
{
	short int num = 0;
	while( tasks[num].func != fn) {
		if ( ++num >= ITEM_COUNT ) {
			return NULL;
		}
	}
	return &tasks[num];
}

void pts_setmask_to( void (*fn)(arg_t), arg_t msk)
{
	short int num = 0;
	while( tasks[num].func != fn) { // If not our
		if ( ++num >= ITEM_COUNT ) {
			return;
		}
	}
	again_fl = true;
	tasks[num].stat |= msk;
}
