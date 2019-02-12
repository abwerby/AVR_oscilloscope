/*
 * SPI_prog.c
 *
 *  Created on: Nov 30, 2018
 *      Author: abood
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "SPI_reg.h"
#include "SPI_int.h"
#include "SPI_priv.h"
#include "SPI_cfg.h"


void SPI_VidInit(void)
{
	/* set clock prescaler */
	CLR_BIT(SPCR,SPR0);
	CLR_BIT(SPCR,SPR1);
	SET_BIT(SPSR,SPI2X);
	//SPSR=(1<<SPI2X);

	/* SET MODE 1  */
	CLR_BIT(SPCR,CPOL);
	CLR_BIT(SPCR,CPHA);

	/* SET COMM_MODE */
	if(COMM_MODE == MASTER_MODE)
	{
		SET_BIT(SPCR,MSTR);
	}
	else if(COMM_MODE == SLAVE_MODE)
	{
		CLR_BIT(SPCR,MSTR);
	}
	else
	{
		/* do nothing */
	}

	/* ENABLE SPI */
	SET_BIT(SPCR,SPE);



}


u8 SPI_u8SendReceiveData(u8 u8DataSend)
{
	/* SET DATA TO SEND */
	SPDR = u8DataSend ;

	/* wait till transmission complete (SPIF flag set) */
	while(GET_BIT(SPSR,SPIF) == 0);

	/* return read data */

	return SPDR;
}


