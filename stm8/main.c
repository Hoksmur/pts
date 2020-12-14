#include <stdint.h>
#include <stm8s.h>
#include "pts.h"
#include "avmacro.h"
#include "defines.h" /* AVMacro  and SDCC helper */

/* sheduler settings in pts.h */
// = #define ITEM_COUNT 4
// = #define USE_TAB

#define LED PB5
#define GND PD3
#define BTN PD2
#define OC_STEP  937U


pts_task_t *event_desc;
void task_event( arg_t arg);	// Receiver IRQ's signal
void task_led( arg_t arg);		// LED's owner
void task_button( arg_t arg);	// Button's owner
enum led_cmd_e { cmd_off=1, cmd_on, cmd_work, cmd_swap_speed } led_cmd;


void initTimer( void )
{
	const uint16_t arrVal = 0xFFFF - 5U + 1U ;
	
	TIM2->ARRH = (uint8_t)(arrVal>>8);
	TIM2->ARRL = (uint8_t) arrVal;
	TIM2->PSCR= 0; // 2^N divider		// init divider register /128	
	TIM2->CR1 |= TIM2_CR1_ARPE | TIM2_CR1_URS;		// enable timer, update on overflow
	TIM2->IER |= TIM2_IER_UIE;			// enable overflow interrupt
	TIM2->EGR |= TIM2_EGR_UG;			// Generate update event
	TIM2->CR1 |= TIM2_CR1_CEN; 			// Enable count
}


int main( void )
{
    // GPIO setup
	pin_mode(GND, OUT_PUSHPULL);
	pin_mode(LED, OUT_PUSHPULL);
	pin_write(LED, 0);
	pin_mode(BTN, IN_PULLUP_NOINT);
	
	pts_task_init( task_event, 0);
	pts_task_init( task_button, 0);
	pts_task_init( task_led, 0);
	event_desc = pts_get_desc( task_event);

	// initialize timer
	CLK-> PCKENR1 |= CLK_PCKENR1_TIM2;	// Enable clock
	initTimer(); 
	enableInterrupts();

    // main loop
    for(;;){
        wfi();
		pts_run_chain();
    }
}


ISR( ISR_TIM2_Upd_Ovf )
{
	event_desc->stat = 0x01 | pin_read(BTN); // Call task: Px5 not 0x01
	TIM2->SR1 &= ~TIM2_SR1_UIF;		// clear flag
}


void task_event( arg_t arg)
{
	pts_set_to( task_button, arg); 	// 'arg' is always not zero
	pts_set_to( task_led, cmd_work);
}


void task_button( arg_t arg)
{
	arg;
	const  uint16_t long_press = 40;
	static uint16_t delay = 0; // Every 
	if ( 0 == pin_read(BTN) ) {
		if ( delay < long_press ) {
			delay++;
			pts_set_to( task_led, cmd_off);	// Override LED's command from task_event()
		} else if ( delay == long_press ) {
			delay++;
			pts_set_to( task_led, cmd_swap_speed );	// Override LED's command from task_event()
		} else {
			pts_set_to( task_led, cmd_on );	// Override LED's command from task_event()
		}
		
	} else {
		// Not override , just reset delay.
		delay = 0;
	}
	
}


void task_led( arg_t arg)
{
	const uint16_t cycles[2] = { 40, 10 };
	static  uint16_t count = 40;
	static  uint8_t idx = 0;
	switch ( arg) {
		case cmd_on:
			pin_write( LED, 0);
			break;
		case cmd_off:
			pin_write( LED, 1);
			break;
		case cmd_work:
			if ( ! --count ) {
				pin_toggle( LED);
				count = cycles[idx];
			}
			break;
		case cmd_swap_speed:
			idx = (idx + 1) & 0x01;
			count = cycles[idx];
			break;
		default:
			break;
	}
}