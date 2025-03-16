/*
 * uart.c
 *
 *  Created on: Mar 13, 2025
 *      Author: Val
 */
#include<stdint.h>
#include "uart.h"

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
void uart_write(int ch);

int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void debug_uart_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER &= ~(3U<<4);
	GPIOA->MODER |= (2U<<4);

	GPIOA->AFR[0] &= ~(15<<8);
	GPIOA->AFR[0] |= (7<<8);

	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);

	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;


}

void uart_write(int ch)
{
	while(!(USART2->SR & SR_TXE)){}
	USART2->DR = (ch & 0xff);

}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate)
{
	USART2->BRR	= compute_uart_bd(periph_clk, baudrate);
}
