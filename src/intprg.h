/*
 * intprg.h
 *
 *  Created on: 2024/03/18
 *      Author: sata
 */

#ifndef INTPRG_H_
#define INTPRG_H_

#include "common.h"

// プロトタイプ宣言
extern void selective_interrupt_create(void);
extern void group_interrupt_create(void);

// 外部定義関数読み込み
extern void INT_Excep_SCI8_TEI8(void);
extern void INT_Excep_SCI8_ERI8(void);

#endif /* INTPRG_H_ */
