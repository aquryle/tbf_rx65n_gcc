/*
 * sci8.c
 *
 *  Created on: 2024/03/18
 *      Author: sata
 */

#include <sci8.h>

volatile uint8_t *sci8_tx_addr;
volatile uint8_t *sci8_rx_addr;
volatile uint16_t sci8_tx_num;
volatile uint16_t sci8_rx_num;
volatile uint16_t sci8_rx_len;
volatile uint8_t sci8_send_end;



void sci8_create(void)
{
	// モジュールストップ解除
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(SCI8) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	// 割り込み優先
	IPR(SCI8, RXI8) = _IPR_LEVEL10;
	IPR(SCI8, TXI8) = _IPR_LEVEL10;

	// レジスタクリア
	SCI8.SCR.BYTE = 0;
	SCI8.SIMR1.BIT.IICM = 0;
	SCI8.SPMR.BYTE = 0;

	// 115200 bps
	SCI8.SMR.BYTE = 0x02;		// PCLKを16分周
	SCI8.SCMR.BYTE = 0x72;		//
	SCI8.SEMR.BYTE = 0x10;
	SCI8.BRR = 0x00;

	// ピンconfig.
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PC6PFS.BYTE = 0x0A;
	MPC.PC7PFS.BYTE = 0x0A;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;

	PORTC.PMR.BIT.B6 = 1;
	PORTC.PODR.BIT.B7 = 1;
	PORTC.PDR.BIT.B7 = 1;
}


void sci8_start(void)
{
	IR(SCI8, TXI8) = 0;
	IR(SCI8, RXI8) = 0;

	IEN(SCI8, TXI8) = 1;
	ICU.GENBL1.BIT.EN24 = 1;
	IEN(SCI8, RXI8) = 1;
	ICU.GENBL1.BIT.EN25 = 1;
}

void sci8_stop(void)
{
	PORTC.PMR.BIT.B7 = 0;

	SCI8.SCR.BIT.TE = 0U;
	SCI8.SCR.BIT.RE = 0U;
	SCI8.SCR.BIT.TIE = 0U;
	SCI8.SCR.BIT.RIE = 0U;

	IEN(SCI8, TXI8) = 0;
	ICU.GENBL1.BIT.EN24 = 0;
	IR(SCI8, TXI8) = 0;
	IEN(SCI8, RXI8) = 0;
	ICU.GENBL1.BIT.EN25 = 0;
	IR(SCI8, RXI8) = 0;
}

void sci8_send(uint8_t *const tx_buf, uint16_t tx_num)
{
	if (1 > tx_num) return;
	else if (0 == IEN(SCI8, TXI8)) return;
	else {
		sci8_tx_addr = tx_buf;
		sci8_tx_num = tx_num;
		IEN(SCI8, TXI8) = 0;
		// SCI8.SCR.BIT.TIE = 1;
		// SCI8.SCR.BIT.TE = 1;
		SCI8.SCR.BYTE |= 0xA0;	// TIEとTEは同時に1にする。TN-RX*-A0235B/J参照
		PORTC.PMR.BIT.B7 = 1;
		IEN(SCI8, TXI8) = 1;
	}

	sci8_send_end = 0;
}

void sci8_recv(uint8_t *const rx_buf, uint16_t rx_num)
{
	if (1 > rx_num) return;
	else {
		sci8_rx_num = 0;
		sci8_rx_len = rx_num;
		sci8_rx_addr = rx_buf;
		SCI8.SCR.BIT.RIE = 1U;
		SCI8.SCR.BIT.RE = 1U;
	}
}

// SCI8 TXI8
void INT_Excep_SCI8_TXI8(void)
{
	if (0 < sci8_tx_num) {
		SCI8.TDR = *sci8_tx_addr;
		sci8_tx_addr++;
		sci8_tx_num--;
	}
	else {
		SCI8.SCR.BIT.TIE = 0;
		SCI8.SCR.BIT.TEIE = 1;
	}
}

// SCI8 RXI8
void INT_Excep_SCI8_RXI8(void)
{
	if (sci8_rx_len > sci8_rx_num) {
		*sci8_rx_addr = SCI8.RDR;
		sci8_rx_addr++;
		sci8_rx_num++;
	}

	if (sci8_rx_len <= sci8_rx_num) {
		SCI8.SCR.BIT.RIE = 0;
		SCI8.SCR.BIT.RE = 0;
	}
}


void INT_Excep_SCI8_TEI8(void)
{
	PORTC.PMR.BYTE &= 0x7FU;

	SCI8.SCR.BIT.TIE = 0U;
	SCI8.SCR.BIT.TE = 0U;
	SCI8.SCR.BIT.TEIE = 0U;

	sci8_send_end = 1;
}

void INT_Excep_SCI8_ERI8(void)
{
	uint8_t err_type;


	/* Clear overrun, framing and parity error flags */
	err_type = SCI8.SSR.BYTE;
	err_type &= 0xC7U;
	err_type |= 0xC0U;
	SCI8.SSR.BYTE = err_type;
}


