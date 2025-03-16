/*
 * adc.c
 *
 *  Created on: Mar 15, 2025
 *      Author: Val
 */

#include "adc.h"
#include "stm32f4xx.h"

#define GPIOAEN		(1)
#define ADC1EN		(1U<<8)
#define ADC_CH1		(1)
#define SR_EOC		(1U<<1)

void pa1_adc_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (3U<<2);
	RCC->APB2ENR |= ADC1EN;
	ADC1->SQR3 = ADC_CH1;
	ADC1->SQR1 = 0;
	ADC1->CR2 |= 1;
}

void start_conversion(void)
{
	ADC1->CR2 |= (1U<<1);
	ADC1->CR2 |= (1U<<30);
}

uint32_t adc_read(void)
{
	while(!(ADC1->SR & SR_EOC)){}
	return (ADC1->DR);
}
