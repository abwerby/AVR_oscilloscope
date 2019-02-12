/*
 * ADC_reg.h
 *
 *  Created on: Nov 3, 2018
 *      Author: HOSNY
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_

#define ADMUX  (*(volatile u8*)0x27)
#define ADCSRA (*(volatile u8*)0x26)
#define ADCH   (*(volatile u8*)0x25)
#define ADCL   (*(volatile u8*)0x24)
#define ADC    (*(volatile u16*)0x24)

/* ADMUX bits */
#define REFS0  6
#define REFS1  7

/* ADCSRA bits */
#define ADEN 7
#define ADSC 6
#define ADIF 4
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

#endif /* ADC_REG_H_ */
