/*
 * adc.c
 *
 *  Created on: 2024/03/22
 *      Author: sata
 */

#include "adc.h"



void adc_create(void)
{
	PORT4.PMR.BYTE = 0x00;
	PORT4.PDR.BYTE - 0x00;


	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(S12AD) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P40PFS.BYTE = 0x80;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;

	S12AD.ADCSR.WORD = 0x0000;
	S12AD.ADCSR.BIT.ADCS = 2;
	S12AD.ADANSA0.BIT.ANSA000 = 1;
	S12AD.ADCSR.BIT.ADST = 1;
}


void adc_start(void)
{

}



//! ADCからの取得値を電圧(mV)に変換する
uint16_t convert_16_voltage(uint16_t value)
{
	uint32_t tmp;
	tmp = VCC_VOLTAGE * value;
	return (uint16_t)(tmp / 0x0FFFu);
}


