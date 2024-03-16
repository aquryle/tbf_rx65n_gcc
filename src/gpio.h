/*
 * gpio.h
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"


typedef enum {
	LED0,
	LED1
} LED_NUM;

typedef enum {
	LED_ON = 0,
	LED_OFF = 1
} LED_STAT;

extern void gpio_create(void);
extern void led_ctrl(LED_NUM num, LED_STAT stat);
extern void led_toggle(LED_NUM num);


#endif /* GPIO_H_ */

