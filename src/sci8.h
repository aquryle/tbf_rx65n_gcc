/*
 * sci8.h
 *
 *  Created on: 2024/03/18
 *      Author: sata
 */

#ifndef SCI8_H_
#define SCI8_H_

#include "common.h"

void INT_Excep_SCI8_TXI8(void);
void INT_Excep_SCI8_RXI8(void);


extern void sci8_create(void);
extern void sci8_start(void);
extern void sci8_stop(void);
extern void sci8_send(uint8_t *const tx_buf, uint16_t tx_num);
extern void sci8_recv(uint8_t *const rx_buf, uint16_t rx_num);

extern void INT_Excep_SCI8_TEI8(void);
extern void INT_Excep_SCI8_ERI8(void);


#endif /* SCI8_H_ */
