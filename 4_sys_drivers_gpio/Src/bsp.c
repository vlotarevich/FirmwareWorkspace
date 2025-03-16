/*
 * bsp.c
 *
 *  Created on: Mar 15, 2025
 *      Author: Val
 */

#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN		(1)
#define GPIOCEN		(1U<<2)
#define PIN5		(1U<<5)
#define LED_PIN		PIN5
#define PIN13		(1U<<13)
#define BTN_PIN		PIN13

void led_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);
}

void led_on(void)
{
	GPIOA->ODR |= LED_PIN;
}

void led_off(void)
{
	GPIOA->ODR &= ~LED_PIN;
}

void button_init(void)
{
	RCC->AHB1ENR |= GPIOCEN;
	GPIOC->MODER  &=~(3U<26);
}

bool get_btn_state(void)
{
	if(GPIOC->IDR & BTN_PIN)
		return false;
	else
		return true;

}



