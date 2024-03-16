/************************************************************************
*
* Device     : RX/RX600/RX65N
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 0.5A  (2015-11-20)  [Hardware Manual Revision : 0.50]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2015 Renesas Electronics Corporation.
*
************************************************************************/

#include "iodefine.h"

#include <stdint.h>

#define R_BSP_NOP()    __asm("nop")


// board config.
#define PIN_SIZE			(100)
#define CRYSTAL_FREQUENCY	(14745600)


static void clockSetup(void);
static void nonExistPortInitialize(void);

extern void HardwareSetup(void);




// 存在しないポートの構成
#if ((PIN_SIZE == 177) || (PIN_SIZE == 176))
#define DEF_P0PDR	(0x50)	/* non-existent pin: P04 P06 */
#define DEF_P1PDR	(0x00)	/* non-existent pin: none */
#define DEF_P2PDR	(0x00)	/* non-existent pin: none */
#define DEF_P3PDR	(0x00)	/* non-existent pin: none */
#define DEF_P4PDR	(0x00)	/* non-existent pin: none */
#define DEF_P5PDR	(0x00)	/* non-existent pin: none */
#define DEF_P6PDR	(0x00)	/* non-existent pin: none */
#define DEF_P7PDR	(0x00)	/* non-existent pin: none */
#define DEF_P8PDR	(0x00)	/* non-existent pin: none */
#define DEF_P9PDR	(0x00)	/* non-existent pin: none */
#define DEF_PAPDR	(0x00)	/* non-existent pin: none */
#define DEF_PBPDR	(0x00)	/* non-existent pin: none */
#define DEF_PCPDR	(0x00)	/* non-existent pin: none */
#define DEF_PDPDR	(0x00)	/* non-existent pin: none */
#define DEF_PEPDR	(0x00)	/* non-existent pin: none */
#define DEF_PFPDR	(0xC0)	/* non-existent pin: PF6 PF7 */
#define DEF_PGPDR	(0x00)	/* non-existent pin: none */
#define DEF_PJPDR	(0xD0)	/* non-existent pin: PJ4 PJ6 PJ7 */
#elif ((PIN_SIZE == 145) || (PIN_SIZE == 144))
#define DEF_P0PDR	(0x50)	/* non-existent pin: P04 P06 */
#define DEF_P1PDR	(0x03)	/* non-existent pin: P10 P11 */
#define DEF_P2PDR	(0x00)	/* non-existent pin: none */
#define DEF_P3PDR	(0x00)	/* non-existent pin: none */
#define DEF_P4PDR	(0x00)	/* non-existent pin: none */
#define DEF_P5PDR	(0x80)	/* non-existent pin: P57 */
#define DEF_P6PDR	(0x00)	/* non-existent pin: none */
#define DEF_P7PDR	(0x00)	/* non-existent pin: none */
#define DEF_P8PDR	(0x30)	/* non-existent pin: P84 P85 */
#define DEF_P9PDR	(0xF0)	/* non-existent pin: P94 P95 P96 P97 */
#define DEF_PAPDR	(0x00)	/* non-existent pin: none */
#define DEF_PBPDR	(0x00)	/* non-existent pin: none */
#define DEF_PCPDR	(0x00)	/* non-existent pin: none */
#define DEF_PDPDR	(0x00)	/* non-existent pin: none */
#define DEF_PEPDR	(0x00)	/* non-existent pin: none */
#define DEF_PFPDR	(0xDF)	/* non-existent pin: PF0 PF1 PF2 PF3 PF4 PF6 PF7 */
#define DEF_PGPDR	(0xFF)	/* non-existent pin: PG0 PG1 PG2 PG3 PG4 PG5 PG6 PG7 */
#define DEF_PJPDR	(0xD7)	/* non-existent pin: PJ0 PJ1 PJ2 PJ4 PJ6 PJ7 */
#elif (PIN_SIZE == 100)
#define DEF_P0PDR	(0x5F)	/* non-existent pin: P00 P01 P02 P03 P04 P06 */
#define DEF_P1PDR	(0x03)	/* non-existent pin: P10 P11 */
#define DEF_P2PDR	(0x00)	/* non-existent pin: none */
#define DEF_P3PDR	(0x00)	/* non-existent pin: none */
#define DEF_P4PDR	(0x00)	/* non-existent pin: none */
#define DEF_P5PDR	(0xC0)	/* non-existent pin: P56 P57 */
#define DEF_P6PDR	(0xFF)	/* non-existent pin: P60 P61 P62 P63 P64 P65 P66 P67 */
#define DEF_P7PDR	(0xFF)	/* non-existent pin: P70 P71 P72 P73 P74 P75 P76 P77 */
#define DEF_P8PDR	(0xFF)	/* non-existent pin: P80 P81 P82 P83 P84 P85 P86 P87 */
#define DEF_P9PDR	(0xFF)	/* non-existent pin: P90 P91 P92 P93 P94 P95 P96 P97 */
#define DEF_PAPDR	(0x00)	/* non-existent pin: none */
#define DEF_PBPDR	(0x00)	/* non-existent pin: none */
#define DEF_PCPDR	(0x00)	/* non-existent pin: none */
#define DEF_PDPDR	(0x00)	/* non-existent pin: none */
#define DEF_PEPDR	(0x00)	/* non-existent pin: none */
#define DEF_PFPDR	(0xFF)	/* non-existent pin: PF0 PF1 PF2 PF3 PF4 PF5 PF6 PF7 */
#define DEF_PGPDR	(0xFF)	/* non-existent pin: PG0 PG1 PG2 PG3 PG4 PG5 PG6 PG7 */
#define DEF_PJPDR	(0xF7)	/* non-existent pin: PJ0 PJ1 PJ2 PJ4 PJ5 PJ6 PJ7 */
#elif (PIN_SIZE == 64)
#define DEF_P0PDR	(0xDF)	/* non-existent pin: P00 P01 P02 P03 P04 P06 P07 */
#define DEF_P1PDR	(0x33)	/* non-existent pin: P10 P11 P14 P15 */
#define DEF_P2PDR	(0x3F)	/* non-existent pin: P20 P21 P22 P23 P24 P25 */
#define DEF_P3PDR	(0x0C)	/* non-existent pin: P32 P33 */
#define DEF_P4PDR	(0xF0)	/* non-existent pin: P44 P45 P46 P47 */
#define DEF_P5PDR	(0xF7)	/* non-existent pin: P50 P51 P52 P54 P55 P56 P57 */
#define DEF_P6PDR	(0xFF)	/* non-existent pin: P60 P61 P62 P63 P64 P65 P66 P67 */
#define DEF_P7PDR	(0xFF)	/* non-existent pin: P70 P71 P72 P73 P74 P75 P76 P77 */
#define DEF_P8PDR	(0xFF)	/* non-existent pin: P80 P81 P82 P83 P84 P85 P86 P87 */
#define DEF_P9PDR	(0xFF)	/* non-existent pin: P90 P91 P92 P93 P94 P95 P96 P97 */
#define DEF_PAPDR	(0x29)	/* non-existent pin: PA0 PA3 PA5 */
#define DEF_PBPDR	(0x1F)	/* non-existent pin: PB0 PB1 PB2 PB3 PB4 */
#define DEF_PCPDR	(0x0C)	/* non-existent pin: PC2 PC3 */
#define DEF_PDPDR	(0x03)	/* non-existent pin: PD0 PD1 */
#define DEF_PEPDR	(0x38)	/* non-existent pin: PE3 PE4 PE5 */
#define DEF_PFPDR	(0xFF)	/* non-existent pin: PF0 PF1 PF2 PF3 PF4 PF5 PF6 PF7 */
#define DEF_PGPDR	(0xFF)	/* non-existent pin: PG0 PG1 PG2 PG3 PG4 PG5 PG6 PG7 */
#define DEF_PJPDR	(0xFF)	/* non-existent pin: PJ0 PJ1 PJ2 PJ3 PJ4 PJ5 PJ6 PJ7 */
#else
#endif




/**
 * @brief	Initial nonexistent port settings
 * @details	Makes initial settings to the port direction registers corresponding to the pins of nonexistent port.
 */
void nonExistPortInitialize(void)
{
	/* PDR - Port Direction Register
	   0:Input(Function as an input pin.)
	   1:Output(Function as an output pin.)*/

	/* Casting the 8bit,because an operation result is 32bit. */

#if (DEF_P0PDR != 0x00)
	PORT0.PDR.BYTE = (uint8_t)(PORT0.PDR.BYTE | DEF_P0PDR);
#endif
#if (DEF_P1PDR != 0x00)
	PORT1.PDR.BYTE = (uint8_t)(PORT1.PDR.BYTE | DEF_P1PDR);
#endif
#if (DEF_P2PDR != 0x00)
	PORT2.PDR.BYTE = (uint8_t)(PORT2.PDR.BYTE | DEF_P2PDR);
#endif
#if (DEF_P3PDR != 0x00)
	PORT3.PDR.BYTE = (uint8_t)(PORT3.PDR.BYTE | DEF_P3PDR);
#endif
#if (DEF_P4PDR != 0x00)
	PORT4.PDR.BYTE = (uint8_t)(PORT4.PDR.BYTE | DEF_P4PDR);
#endif
#if (DEF_P5PDR != 0x00)
	 PORT5.PDR.BYTE = (uint8_t)(PORT5.PDR.BYTE | DEF_P5PDR);
#endif
#if (DEF_P6PDR != 0x00)
	PORT6.PDR.BYTE = (uint8_t)(PORT6.PDR.BYTE | DEF_P6PDR);
#endif
#if (DEF_P7PDR != 0x00)
	PORT7.PDR.BYTE = (uint8_t)(PORT7.PDR.BYTE | DEF_P7PDR);
#endif
#if (DEF_P8PDR != 0x00)
	PORT8.PDR.BYTE = (uint8_t)(PORT8.PDR.BYTE | DEF_P8PDR);
#endif
#if (DEF_P9PDR != 0x00)
	PORT9.PDR.BYTE = (uint8_t)(PORT9.PDR.BYTE | DEF_P9PDR);
#endif
#if (DEF_PAPDR != 0x00)
	PORTA.PDR.BYTE = (uint8_t)(PORTA.PDR.BYTE | DEF_PAPDR);
#endif
#if (DEF_PBPDR != 0x00)
	PORTB.PDR.BYTE = (uint8_t)(PORTB.PDR.BYTE | DEF_PBPDR);
#endif
#if (DEF_PCPDR != 0x00)
	PORTC.PDR.BYTE = (uint8_t)(PORTC.PDR.BYTE | DEF_PCPDR);
#endif
#if (DEF_PDPDR != 0x00)
	PORTD.PDR.BYTE = (uint8_t)(PORTD.PDR.BYTE | DEF_PDPDR);
#endif
#if (DEF_PEPDR != 0x00)
	PORTE.PDR.BYTE = (uint8_t)(PORTE.PDR.BYTE | DEF_PEPDR);
#endif
#if (DEF_PFPDR != 0x00)
	PORTF.PDR.BYTE = (uint8_t)(PORTF.PDR.BYTE | DEF_PFPDR);
#endif
#if (DEF_PGPDR != 0x00)
	PORTG.PDR.BYTE = (uint8_t)(PORTG.PDR.BYTE | DEF_PGPDR);
#endif
#if (DEF_PJPDR != 0x00)
	PORTJ.PDR.BYTE = (uint8_t)(PORTJ.PDR.BYTE | DEF_PJPDR);
#endif
}


/**
 * @brief	Setup clock
 * @details	PLL is used as system clock. PLL sourse is external crystal.\n
 * 			Clock (main clock: 14.7456 MHz)\n
 * 			FCLK:	58.9824 MHz \n	ICLK:	117.9648 MHz \n
 * 			PCLKA:	117.9648 MHz \n	PCLKB:	29.4912 MHz \n
 * 			PCLKC:	29.4912 MHz \n	PCLKD:	29.4912 MHz \n
 * 			BCLK:	117.9648 MHz \n	CANMC:	14.7456 MHz \n
 */
void clockSetup(void)
{
	uint32_t tmp32;

	// Protected register write enable.
	SYSTEM.PRCR.WORD = 0xA50Bu;

	// HOCO power off
	if (0 == SYSTEM.HOCOCR.BIT.HCSTP) {
		SYSTEM.HOCOCR.BIT.HCSTP = 1;
		if (0 == SYSTEM.HOCOCR.BYTE) R_BSP_NOP();
		while (0 != SYSTEM.OSCOVFSR.BIT.HCOVF) {

		}
	}
	SYSTEM.HOCOPCR.BIT.HOCOPCNT = 1;

	// main clock operation
	if (0x011 == SYSTEM.MOSCCR.BYTE) SYSTEM.MOSCCR.BYTE = 0x01;
	SYSTEM.MOFCR.BIT.MODRV2 = 2;				// Main clock frequency: 8.1~16 MHz
	while (2 != SYSTEM.MOFCR.BIT.MODRV2);
	SYSTEM.MOSCWTCR.BYTE = 0x0Fu;				// Main clock oscillator wait: max
	SYSTEM.MOSCCR.BYTE = 0x00u;					// Main clock: start
	while (0 != SYSTEM.MOSCCR.BYTE);
	if (1 == SYSTEM.MOSCCR.BYTE) R_BSP_NOP();
	while (1 != SYSTEM.OSCOVFSR.BIT.MOOVF);	// Waiting until main clock stable.

	// ROM wait setting
	SYSTEM.ROMWT.BIT.ROMWT = 2;
	if (2 == SYSTEM.ROMWT.BIT.ROMWT) R_BSP_NOP();

	// PLL setting
	SYSTEM.PLLCR.BIT.STC = 0x1F;			// PLL multiple x16.0
	SYSTEM.PLLCR.BIT.PLLSRCSEL = 0;			// PLL clock source: main clock
	SYSTEM.PLLCR.BIT.PLIDIV = 0;			// PLL divide /1
	SYSTEM.PLLCR2.BIT.PLLEN = 0;			// PLL start
	while (1 != SYSTEM.OSCOVFSR.BIT.PLOVF); // Waiting until PLL stable.

	// peripheral clock division
	tmp32 = 0;
	tmp32 |= 0x20000000;	// FCK	1/4
	tmp32 |= 0x01000000;	// ICK	1/2
	tmp32 |= 0x00800000;	// BCLK出力なし
	tmp32 |= 0x00400000;	// SDCLK出力なし
	tmp32 |= 0x00010000;	// BCK	1/2
	tmp32 |= 0x00001000;	// PCKA	1/2
	tmp32 |= 0x00000300;	// PCKB	1/8
	tmp32 |= 0x00000030;	// PCKC	1/8
	tmp32 |= 0x00000003;	// PCKD	1/8
	SYSTEM.SCKCR.LONG = tmp32;
	while (SYSTEM.SCKCR.LONG != tmp32);

	// select clock source
	SYSTEM.SCKCR3.WORD = 0x0400;			// System clock: PLL
	while (SYSTEM.SCKCR3.WORD != 0x0400);
	SYSTEM.LOCOCR.BYTE = 0x01;				// LOCO stop

	// Protected register write disable.
	SYSTEM.PRCR.WORD = 0xA500;
}




void HardwareSetup(void)
{
	clockSetup();					// クロック設定
	nonExistPortInitialize();		// 存在しないポートの初期化
}
