/*
 * cmt.h
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#ifndef CMT_H_
#define CMT_H_


#include "common.h"
#include "interrupt_handlers.h"

//! CMTW0の割り込み発生フラグ
extern volatile uint8_t cmtw0_ir;
//! CMTW1の割り込み発生フラグ
extern volatile uint8_t cmtw1_ir;


extern void cmt_create(void);
extern void cmt_wait(uint8_t cmt_num, CMT_UNIT unit, uint32_t t);
extern void cmtw0_start(CMT_UNIT unit, uint32_t time);
extern void cmtw1_start(CMT_UNIT unit, uint32_t time);



#endif /* CMT_H_ */
