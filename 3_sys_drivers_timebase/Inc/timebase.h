/*
 * timebase.h
 *
 *  Created on: Mar 14, 2025
 *      Author: Val
 */

#ifndef TIMEBASE_H_
#define TIMEBASE_H_

#include <stdint.h>

uint32_t get_tick(void);
void delay(uint32_t delay);
void timebase_init(void);

#endif /* TIMEBASE_H_ */
