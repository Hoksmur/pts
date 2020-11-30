#include "pts.h"
#include <stdbool.h>
//  #include <stdio.h>

#ifdef TAB_SZ
static struct pts_task_desc tasks[TAB_SZ];
#else
#include <malloc.h>
static struct pts_task_desc pts_entry = {.stat=0, .next=NULL, .func=NULL };
#endif

static bool again_fl = false;


void pts_task_init( void(*fn)(arg_t), arg_t st)
{
#ifdef TAB_SZ
	short i = 0;
	struct pts_task_desc *p_tsk = &tasks[0];
	while( (p_tsk->func != NULL) && (i<TAB_SZ)  ) {
		i++, p_tsk = &tasks[i];
	}
	if (p_tsk->func == NULL) {
		p_tsk->func = fn;
		p_tsk->stat = st;
		return;
	}
#else
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
#endif
}


void pts_run_chain(void)
{
#ifdef TAB_SZ
	short int i=0;
	struct pts_task_desc *p_tsk = &tasks[0];
	while(p_tsk->func != NULL) {
		if (p_tsk->stat != 0) {
			(p_tsk->func)(p_tsk->stat); // Call task's function
			p_tsk->stat = 0;            // then clar state
			if (again_fl)  { i=0, p_tsk = &tasks[0]; };  // Rerun chain if any 'stat' changed 
			/* Use flag to prevent pass from begin after every task.*/
			continue;
		}
		if ( i>=TAB_SZ ) {
			break;
		}
		i++, p_tsk = &tasks[i];
	}
#else
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != NULL) {
		if (p_tsk->stat != 0) {
			(p_tsk->func)(p_tsk->stat); // Call task's function
			p_tsk->stat = 0;            // then clar state
			if (again_fl)  p_tsk = &pts_entry;  // Rerun chain if any 'stat' changed 
			/* Use flag to prevent pass from begin after every task.*/
			continue;
		}
		if ( p_tsk->next == NULL) {
			break;
		}
		p_tsk = p_tsk->next;
	}
#endif
}


void pts_set_to( void (*fn)(arg_t), arg_t st)
{
#ifdef TAB_SZ
	short int i=0;
	struct pts_task_desc *p_tsk = &tasks[0];
	while( p_tsk->func != fn) {
		if ( i>=TAB_SZ ) {
			return;
		}
		i++, p_tsk = &tasks[i];
	}
	again_fl = true;
	p_tsk->stat = st;
#else
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			return;
		}
		p_tsk = p_tsk->next;
	}
	again_fl = true;
	p_tsk->stat = st;
#endif
}

#if 0
#include <stdio.h>
void chain_print(void)
{
#ifdef TAB_SZ
	short int i=0;
	struct pts_task_desc *p_tsk = &tasks[i];
	while( i<TAB_SZ) {
		printf("  .func %X\t", p_tsk->func);
		printf("  .stat %d\t", p_tsk->stat);
		i++, p_tsk = &tasks[i];
	}
	printf("\n");
#else
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
#endif
}
#endif

struct pts_task_desc *pts_get_desc( void (*fn)(arg_t) )
{
#ifdef TAB_SZ
	short int i=0;
	struct pts_task_desc *p_tsk = &tasks[0];
	while( p_tsk->func != fn) {
		if ( i>=TAB_SZ ) {
			p_tsk = NULL;
			break;
		}
		i++, p_tsk = &tasks[i];
	}
	return p_tsk;
#else
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			p_tsk = NULL;
			break;
		}
		p_tsk = p_tsk->next;
	}
	return p_tsk;
#endif
}

void pts_setmask_to( void (*fn)(arg_t), arg_t msk)
{
#ifdef TAB_SZ
	short int i=0;
	struct pts_task_desc *p_tsk = &tasks[i];
	while( p_tsk->func != fn) {
		if ( i >= TAB_SZ) {
			return;
		}
		i++, p_tsk = &tasks[i];
	}
	again_fl = true;
	p_tsk->stat |= msk;
#else
	struct pts_task_desc *p_tsk = &pts_entry;
	while( p_tsk->func != fn) {
		if ( p_tsk->next == NULL) {
			return;
		}
		p_tsk = p_tsk->next;
	}
	again_fl = true;
	p_tsk->stat |= msk;
#endif
}

