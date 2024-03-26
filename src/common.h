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



#define R_BSP_NOP()	__asm("nop")


// board config.
#define RX65N_LITTLE_ENDIAN	(0)
#define RX65N_BIG_ENDIAN		(1)
#define RX65N_BYTE_ORDER		(LITTLE_ENDIAN)
#define VCC_VOLTAGE			(3300u)
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


//! bit
#define _B0		(1u << 0)
#define _B1		(1u << 1)
#define _B2		(1u << 2)
#define _B3		(1u << 3)
#define _B4		(1u << 4)
#define _B5		(1u << 5)
#define _B6		(1u << 6)
#define _B7		(1u << 7)
#define _B8		(1u << 8)
#define _B9		(1u << 9)
#define _B10	(1u << 10)
#define _B11	(1u << 11)
#define _B12	(1u << 12)
#define _B13	(1u << 13)
#define _B14	(1u << 14)
#define _B15	(1u << 15)
#define _B16	(1u << 16)
#define _B17	(1u << 17)
#define _B18	(1u << 18)
#define _B19	(1u << 19)
#define _B20	(1u << 20)
#define _B21	(1u << 21)
#define _B22	(1u << 22)
#define _B23	(1u << 23)
#define _B24	(1u << 24)
#define _B25	(1u << 25)
#define _B26	(1u << 26)
#define _B27	(1u << 27)
#define _B28	(1u << 28)
#define _B29	(1u << 29)
#define _B30	(1u << 30)
#define _B31	(1u << 31)

//! Interrupt Priority Level
#define _IPR_LEVEL0		(0x00u)
#define _IPR_LEVEL1		(0x01u)
#define _IPR_LEVEL2		(0x02u)
#define _IPR_LEVEL3		(0x03u)
#define _IPR_LEVEL4		(0x04u)
#define _IPR_LEVEL5		(0x05u)
#define _IPR_LEVEL6		(0x06u)
#define _IPR_LEVEL7		(0x07u)
#define _IPR_LEVEL8		(0x08u)
#define _IPR_LEVEL9		(0x09u)
#define _IPR_LEVEL10	(0x0Au)
#define _IPR_LEVEL11	(0x0Bu)
#define _IPR_LEVEL12	(0x0Cu)
#define _IPR_LEVEL13	(0x0Du)
#define _IPR_LEVEL14	(0x0Eu)
#define _IPR_LEVEL15	(0x0Fu)




#endif /* COMMON_H_ */
