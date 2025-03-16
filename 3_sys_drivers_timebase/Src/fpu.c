#include "stm32f4xx.h"
#include "fpu.h"

void fpu_enable(void)
{
	SCB->CPACR |= (15U << 20);
}
