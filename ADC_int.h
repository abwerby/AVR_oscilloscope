/*
 * ADC_int.h
 *
 *  Created on: Nov 3, 2018
 *      Author: HOSNY
 */

#define ADC_CHANNEL_0  (u8)0x00
#define ADC_CHANNEL_1  (u8)0x01
#define ADC_CHANNEL_2  (u8)0x02
#define ADC_CHANNEL_3  (u8)0x03
#define ADC_CHANNEL_4  (u8)0x04
#define ADC_CHANNEL_5  (u8)0x05
#define ADC_CHANNEL_6  (u8)0x06
#define ADC_CHANNEL_7  (u8)0x07


void ADC_vidInit(void);

u16 ADC_u16GetAdValue(u8 u8ChannelId);
