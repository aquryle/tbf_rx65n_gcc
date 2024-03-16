/*
 * cmt.h
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#ifndef CMT_H_
#define CMT_H_


#include "common.h"


extern void cmt_create(void);
extern void cmt_wait(uint8_t cmt_num, CMT_UNIT unit, uint32_t t);



#endif /* CMT_H_ */
