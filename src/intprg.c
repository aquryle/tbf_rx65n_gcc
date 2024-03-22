/*
 * intprg.c
 *
 *  Created on: 2024/03/18
 *      Author: sata
 */

#include <intprg.h>



void group_interrupt_create(void)
{
	IEN(ICU, GROUPBL1) = 0;
	IPR(ICU, GROUPBL1) = 10;
	IEN(ICU, GROUPBL1) = 1;

}

void selective_interrupt_create(void)
{
	// CMT2
	IEN(PERIB, INTB128) = 0;
	ICU.SLIBXR128.BYTE = 0x01;
	IPR(PERIB, INTB128) = _IPR_LEVEL15;
	ICU.SLIPRCR.BIT.WPRC = 1;
	while (1 != ICU.SLIPRCR.BIT.WPRC);

}


void INT_Excep_ICU_GROUPBL1(void)
{
	if (ICU.GRPBL1.BIT.IS24)	INT_Excep_SCI8_TEI8();	// SCI8送信完了
	if (ICU.GRPBL1.BIT.IS25)	INT_Excep_SCI8_ERI8();	// SCI8受信エラー
}

