/*
 * common.h
 *
 *  Created on: 2024/03/14
 *      Author: sata
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "iodefine.h"
#include <stdint.h>
#include "interrupt_handlers.h"


#define R_BSP_NOP()    __asm("nop")


// board config.
#define PIN_SIZE			(100)
#define CRYSTAL_FREQUENCY	(14745600)



/*******************************************************************************
enumrate
*******************************************************************************/
typedef enum {
	MILLI_SEC,
	MICRO_SEC,
	CYCLE
} CMT_UNIT;






#endif /* COMMON_H_ */
