/*
 * intprg.h
 *
 *  Created on: 2024/03/18
 *      Author: sata
 */

#ifndef INTPRG_H_
#define INTPRG_H_

#include "common.h"


extern void group_interrupt_create(void);
extern void INT_Excep_ICU_GROUPBL1(void);



extern void INT_Excep_SCI8_TEI8(void);
extern void INT_Excep_SCI8_ERI8(void);

#endif /* INTPRG_H_ */
