/*
 * cmt.c
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#include "cmt.h"


static uint8_t *cmtw0_status;
static uint8_t *cmtw1_status;
static void cmtw0_stop(void);
static void cmtw1_stop(void);


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
	MSTP(CMT2) = 0;
	MSTP(CMTW0) = 0;
	MSTP(CMTW1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	// カウントストップ
	CMT.CMSTR0.BIT.STR0 = 0;
	CMT.CMSTR0.BIT.STR1 = 0;
	CMT.CMSTR1.BIT.STR2 = 0;
	CMTW0.CMWSTR.BIT.STR = 0;
	CMTW1.CMWSTR.BIT.STR = 0;

	// コントロールレジスタ
	CMT0.CMCR.WORD = 0x0080;	// PCLK/8、CMI禁止
	CMT1.CMCR.WORD = 0x0080;	// PCLK/8、CMI禁止
	CMT2.CMCR.WORD = 0x0083;	// PCLK/512、CMI禁止

	// コンペアマッチ許可（CMTWのみ）
	CMTW1.CMWIOR.BIT.CMWE = 1;	// コンペアマッチ動作許可
	CMTW0.CMWIOR.BIT.CMWE = 1;	// コンペアマッチ動作許可

	// IPR
	IPR(CMTW1, CMWI1) = _IPR_LEVEL10;
	IPR(CMTW0, CMWI0) = _IPR_LEVEL10;
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



/**
 * @brief CMTW0の動作を開始する
 *
 * @param unit timeの単位
 * @param time コンペアマッチまでの時間
 * @param status コンペアマッチしたかフラグ
 *
 * @details	このタイマーは主にタイムアウト監視に使う。
 * 			引数で時間を指定し、コンペアマッチしたら
 * 			ポインタ変数のstatusが1になる。
 */
void cmtw0_start(CMT_UNIT unit, uint16_t time, uint8_t *status)
{
	// 周期設定
	cmtw0_stop();
	switch (unit)
	{
	case MILLI_SEC:
		CMTW0.CMWCR.WORD = 0x000B;	// PCLK/512、CMWI許可
		CMTW0.CMWCOR = 57ul * time;	// コンペアマッチ値設定
		break;
	case MICRO_SEC:
		CMTW0.CMWCR.WORD = 0x0008;	// PCLK/8、CMWI許可
		CMTW0.CMWCOR = 3ul * time;	// コンペアマッチ値設定
		break;
	case CYCLE:
		// 気が向いたらやる
		break;
	}

	// 割り込みステータス用ポインタをコピー
	*status = 0;
	cmtw0_status = status;

	// タイマー開始
	CMTW0.CMWCNT = 0ul;			// カウンタリセット
	IEN(CMTW0, CMWI0) = 1;		// コンペアマッチ割り込み許可
	CMTW0.CMWSTR.BIT.STR = 1;	// タイマー開始
}

/**
 * @brief CMT0を停止する
 *
 */
void cmtw0_stop(void)
{
	CMTW0.CMWSTR.BIT.STR = 0;	// タイマー停止
	IEN(CMTW0, CMWI0) = 0;		// コンペアマッチ割り込み禁止
}


/**
 * @brief CMTW1の動作を開始する
 *
 * @param unit timeの単位
 * @param time コンペアマッチまでの時間
 * @param status コンペアマッチしたかフラグ
 *
 * @details	このタイマーは主にタイムアウト監視に使う。
 * 			引数で時間を指定し、コンペアマッチしたら
 * 			ポインタ変数のstatusが1になる。
 */
void cmtw1_start(CMT_UNIT unit, uint16_t time, uint8_t *status)
{
	// 周期設定
	cmtw1_stop();
	switch (unit)
	{
	case MILLI_SEC:
		CMTW1.CMWCR.WORD = 0x000B;	// PCLK/512、CMWI許可
		CMTW1.CMWCOR = 57ul * time;	// コンペアマッチ値設定
		break;
	case MICRO_SEC:
		CMTW1.CMWCR.WORD = 0x0008;	// PCLK/8、CMWI許可
		CMTW1.CMWCOR = 3ul * time;	// コンペアマッチ値設定
		break;
	case CYCLE:
		// 気が向いたらやる
		break;
	}

	// 割り込みステータス用ポインタをコピー
	*status = 0;
	cmtw1_status = status;

	// タイマー開始
	CMTW1.CMWCNT = 0ul;			// カウンタリセット
	IEN(CMTW1, CMWI1) = 1;		// コンペアマッチ割り込み許可
	CMTW1.CMWSTR.BIT.STR = 1;	// タイマー開始
}

/**
 * @brief CMTW1を停止する
 *
 */
void cmtw1_stop(void)
{
	CMTW1.CMWSTR.BIT.STR = 0;	// タイマー停止
	IEN(CMTW1, CMWI1) = 0;		// コンペアマッチ割り込み禁止
}


void cmt2_start(void)
{
	cmt2_stop();
	CMT2.CMCR.BIT.CMIE = 1;		// 割り込み許可
	CMT2.CMCNT = 0;				// カウンタリセット
	CMT2.CMCOR = 28799;			// コンペアマッチ値設定
	IEN(PERIB, INTB128) = 1;	// 割り込み許可
	CMT.CMSTR1.BIT.STR2 = 1;	// タイマー開始
}

void cmt2_stop(void)
{
	CMT.CMSTR1.BIT.STR2 = 0;
	IEN(PERIB, INTB128) = 0;	// 割り込み禁止
}





// CMTW0 CMWI0
void INT_Excep_CMTW0_CMWI0(void)
{
	*cmtw0_status = 1;
	cmtw0_stop();
}

// CMTW1 CMWI1
void INT_Excep_CMTW1_CMWI1(void)
{
	*cmtw1_status = 1;
	cmtw1_stop();
}





