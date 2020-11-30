#include "pts.h"
#include <malloc.h>
#include <stdbool.h>

static struct pts_task_desc  pts_entry = {.stat=0, .next=NULL, .func=NULL };
static struct pts_task_desc  *task_item;
static bool again_fl = false;

void pts_task_init( void(*fn)(arg_t), arg_t st)
{
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->next != NULL) {
		p_tsk = p_tsk->next;
	}
	if (p_tsk->func == NULL) {
		p_tsk->func = fn;
		p_tsk->stat = st;
		return;
	}
	p_tsk->next = malloc(sizeof(struct pts_task_desc));
	p_tsk = p_tsk->next;
	p_tsk->next = NULL;
	p_tsk->func = fn;
	p_tsk->stat = st;
	return;
}


void pts_run_chain(void)
{
	struct pts_task_desc *p_tsk = &pts_entry;
	 while( p_tsk->func != NULL) {
		if (p_tsk->stat != 0) {
			task_item = p_tsk;
			(p_tsk->func)(p_tsk->stat); // Call task's function
			p_tsk->stat = 0;
			if (again_fl)  p_tsk = &pts_entry;  // Rerun chain if any 'stat' changed 
			/* Use flag to prevent pass from begin after every task.*/
			continue;
		}
		if ( p_tsk->next == NULL) {
			break;
		}
		p_tsk = p_tsk->next;
	}
}


void pts_set_to( void (*fn)(arg_t), arg_t st)
{
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			return;
		}
		p_tsk = p_tsk->next;
	}
	again_fl = true;
	p_tsk->stat = st;
}

#if 0
#include <stdio.h>
void chain_print(void)
{
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->next != NULL) {
		printf("  .func %X\t", p_tsk->func);
		printf("  .stat %d\t", p_tsk->stat);
		printf("  .next %X\n", p_tsk->next);
		p_tsk = p_tsk->next;
	}
	printf("  .func %X\t", p_tsk->func);
	printf("  .stat %d\t", p_tsk->stat);
	printf("  .next %X\n", p_tsk->next);
}
#endif

struct pts_task_desc *pts_get_desc( void (*fn)(arg_t) )
{
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			p_tsk = NULL;
			break;
		}
		p_tsk = p_tsk->next;
	}
	return p_tsk;
}

void pts_setmask_to( void (*fn)(arg_t), arg_t msk)
{
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			return;
		}
		p_tsk = p_tsk->next;
	}
	again_fl = true;
	p_tsk->stat |= msk;
}

