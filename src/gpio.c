/*
 * gpio.c
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#include "gpio.h"


/**
 * @brief GPIO制御
 *
 */
void gpio_create(void)
{
	// LED0, 1
	PORTD.PDR.BIT.B6 = 1;
	PORTD.PDR.BIT.B7 = 1;

	PORTD.PODR.BIT.B6 = 1;
	PORTD.PODR.BIT.B7 = 1;
}


void led_ctrl(LED_NUM num, LED_STAT stat)
{
	switch (num)
	{
	case LED0:
		PORTD.PODR.BIT.B6 = stat;
		break;
	case LED1:
		PORTD.PODR.BIT.B7 = stat;
		break;
	}
}


void led_toggle(LED_NUM num)
{
	switch (num)
	{
	case LED0:
		PORTD.PODR.BYTE ^= _B6;
		break;
	case LED1:
		PORTD.PODR.BYTE ^= _B7;
		break;
	}
}

