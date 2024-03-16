/*
 * cmt.c
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#include "cmt.h"



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
	CMTW0.CMWCR.WORD = 0x000B;	// PCLK/512、CMWI許可
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
	else if (unit == MICRO_SEC)	cnt_max = 1;	// 1.085usでコンペアマッチ
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
			while (CMT0.CMCNT < cnt_max);
		}
		CMT.CMSTR0.BIT.STR1 = 0;
		break;
	}
}

