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

}



