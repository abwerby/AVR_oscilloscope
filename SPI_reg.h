/*
 * SPI_reg.h
 *
 *  Created on: Nov 30, 2018
 *      Author: werby
 */

#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPSR (*(volatile u8*)0x2E)
#define SPCR (*(volatile u8*)0x2D)
#define SPDR (*(volatile u8*)0x2F)

/* register SPSR */
#define SPIF  7
#define SPI2X 0

/* register SPCR */
#define SPE   6
#define DORD  5
#define MSTR  4
#define CPOL  3
#define CPHA  2
#define SPR1  1
#define SPR0  0



#endif /* SPI_REG_H_ */
