/*
 * adc.h
 *
 *  Created on: 2024/03/22
 *      Author: sata
 */

#ifndef ADC_H_
#define ADC_H_

#include "common.h"

extern void adc_create(void);
extern void adc_start(void);
extern uint16_t convert_16_voltage(uint16_t value);


#endif /* ADC_H_ */
