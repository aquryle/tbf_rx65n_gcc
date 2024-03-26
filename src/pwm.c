/*
 * pwm.c
 *
 *  Created on: 2024/03/23
 *      Author: sata
 */

#include "pwm.h"

void pwm_create(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PD6PFS.BIT.PSEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;

	PORTD.PMR.BIT.B6 = 1;



}

