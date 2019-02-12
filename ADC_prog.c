/*
 * ADC_prog.c
 *
 *  Created on: Nov 3, 2018
 *      Author: werby
 */
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "ADC_int.h"
#include "ADC_reg.h"


void ADC_vidInit(void)
{
	/* Choose AREF as reference voltage */
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);

	/* Select division factor to 2 */
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);

	/* Enable ADC */
	SET_BIT(ADCSRA,ADEN);

}

u16 ADC_u16GetAdValue(u8 u8ChannelId)
{
	/* Select required channel ID */
	ADMUX = (ADMUX & ~(0x1F)) | u8ChannelId;

	/* start adc conversion */
	SET_BIT(ADCSRA,ADSC);

	while(GET_BIT(ADCSRA,ADIF) == 0);

	SET_BIT(ADCSRA,ADIF);

	return ADC;

}

