/*
 * cmt.c
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#include "cmt.h"


volatile uint8_t cmtw0_ir;
volatile uint8_t cmtw1_ir;

volatile uint32_t watch32;



/**
 * @brief	コンペアマッチタイマを起動
 * @details	CMTはウェイト、CMTWはタイムアウトチェックで使う
 */
void cmt_create(void)
{
	// モジュールストップ解除
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	MSTP(CMT1) = 0;
	MSTP(CMTW0) = 0;
	MSTP(CMTW1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	// カウントストップ
	CMT.CMSTR0.BIT.STR0 = 0;
	CMT.CMSTR0.BIT.STR1 = 0;
	CMTW0.CMWSTR.BIT.STR = 0;
	CMTW1.CMWSTR.BIT.STR = 0;

	// コントロールレジスタ
	CMT0.CMCR.WORD = 0x0080;	// PCLK/8、CMI禁止
	CMT1.CMCR.WORD = 0x0080;	// PCLK/8、CMI禁止
	CMTW0.CMWCR.WORD = 0x0008;	// PCLK/8、CMWI許可
	CMTW1.CMWCR.WORD = 0x000B;	// PCLK/512、CMWI許可

	CMTW0.CMWIOR.BIT.CMWE = 1;	// コンペアマッチ動作許可
	CMTW1.CMWIOR.BIT.CMWE = 1;	// コンペアマッチ動作許可


	// IPR
	IPR(CMTW1, CMWI1) = _IPR_LEVEL10;


}



/**
 * @brief コンペアマッチタイマを使ったウェイト
 *
 * @param cmt_num CMT0 or CMT1
 * @param unit ウェイト時間単位
 * @param t ウェイト時間
 */
void cmt_wait(uint8_t cmt_num, CMT_UNIT unit, uint32_t t)
{
	uint32_t i = 0;
	uint32_t cnt_max = 0;

	// 引数チェック
	if (2 <= cmt_num) return;
	if (unit != MILLI_SEC && unit != MICRO_SEC && unit != CYCLE) return;
	if (0 == t) return;

	// カウント設定
	if (unit == MILLI_SEC)		cnt_max = 3685;	// 0.999891msでコンペアマッチ
	else if (unit == MICRO_SEC)	cnt_max = 3;	// 1.085usでコンペアマッチ
	else						cnt_max = 3685;

	// ウェイト
	switch (cmt_num)
	{
	case 0:
		CMT.CMSTR0.BIT.STR0 = 1;
		for (i = 0; i < t; i++) {
			CMT0.CMCNT = 0x0000;
			while (CMT0.CMCNT < cnt_max);
		}
		CMT.CMSTR0.BIT.STR0 = 0;
		break;
	case 1:
		CMT.CMSTR0.BIT.STR1 = 1;
		for (i = 0; i < t; i++) {
			CMT1.CMCNT = 0x0000;
			while (CMT1.CMCNT < cnt_max);
		}
		CMT.CMSTR0.BIT.STR1 = 0;
		break;
	}
}


void cmtw0_start(CMT_UNIT unit, uint32_t time)
{
	CMTW0.CMWCOR = 3 * time;	// us単位
	CMTW0.CMWSTR.BIT.STR = 1;
}

void cmtw1_start(CMT_UNIT unit, uint32_t time)
{
	CMTW1.CMWCOR = 57 * time;	// ms単位
	CMTW1.CMWCNT = 0x00000000ul;
	// IR(CMTW1, CMWI1) = 0;
	IEN(CMTW1, CMWI1) = 1;
	CMTW1.CMWSTR.BIT.STR = 1;
}

void cmtw1_stop(void)
{
	// CMTW1.CMWCNT = 0;
	// IR(CMTW1, CMWI1) = 0;
	CMTW1.CMWSTR.BIT.STR = 0;
	IEN(CMTW1, CMWI1) = 0;
}


// CMTW0 CMWI0
void INT_Excep_CMTW0_CMWI0(void)
{
	cmtw0_ir = 1;
}

// CMTW1 CMWI1
void INT_Excep_CMTW1_CMWI1(void)
{
	cmtw1_ir = 1;
	cmtw1_stop();
}

