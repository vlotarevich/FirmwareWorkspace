/*
 * timebase.c
 *
 *  Created on: Mar 14, 2025
 *      Author: Val
 */

#include "timebase.h"
#include "stm32f4xx.h"

#define CTRL_ENABLE			(1<<0)
#define CTRL_TICKINT		(1U<<1)
#define CTRL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)
#define ONE_SEC_LOAD		16000000

#define TICK_FREQ			1
#define MAX_DELAY			0xffffffff
volatile uint32_t	g_curr_tick;
volatile uint32_t	g_curr_tick_p;



void tick_increment(void)
{
	g_curr_tick += TICK_FREQ;
}

void timebase_init(void)
{
	__disable_irq();
	SysTick->LOAD = ONE_SEC_LOAD - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = CTRL_CLKSRC;
	SysTick->CTRL |= CTRL_TICKINT | CTRL_ENABLE;

	__enable_irq();
}

void SysTick_Handler(void)
{
	tick_increment();
}

uint32_t get_tick(void)
{
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();
	return g_curr_tick_p;
}

void delay(uint32_t delay)
{
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;
	if (wait < MAX_DELAY)
	{
		wait += TICK_FREQ;
	}

	while((get_tick() - tickstart) < wait){}
}


