/*
 * ADC_MCP_prog.c
 *
 *  Created on: Feb 7, 2019
 *      Author: ab_werby
 */


#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "avr/io.h"
#include "SPI_int.h"
#include "ADC_MCP_cfg.h"
#include "ADC_MCP_int.h"

u8  val_H , val_L ;
u16 ADC_VAL ;

void Init_ADC_MCP()
{
	SET_BIT(CS_DIR_PORT,CS_PIN) ;        // CS
	CLR_BIT(SPI_DIR_PORT,MISO_PIN) ;    // MISO
	SET_BIT(SPI_DIR_PORT,SCK_PIN) ;    // SCK

	SPI_VidInit();
}


u16 Read_ADC_MCP()
{


	CLR_BIT(CS_PORT,CS_PIN) ;
	val_H = SPI_u8SendReceiveData(0);
	val_L = SPI_u8SendReceiveData(0);
	SET_BIT(CS_PORT,CS_PIN) ;


	ADC_VAL = ((u16)val_H<<8) | (val_L);
	ADC_VAL >>= 3 ;
	ADC_VAL = ADC_VAL & 0x3FF ;

	return ADC_VAL ;
}
