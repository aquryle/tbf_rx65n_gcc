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



void INT_Excep_ICU_GROUPBL1(void)
{
	if (ICU.GRPBL1.BIT.IS24) {
		INT_Excep_SCI8_TEI8();
	}	// SCI8送信完了

	if (ICU.GRPBL1.BIT.IS25) {
		INT_Excep_SCI8_ERI8();
	}	// SCI8受信エラー
}

