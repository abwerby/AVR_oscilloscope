/*
 * TFT_cfg.h
 *
 *  Created on: Jan 23, 2019
 *      Author: abood
 */

#ifndef TFT_CFG_H_
#define TFT_CFG_H_

#define TFT_DATA_PORT   PORTC
#define TFT_CTRL_PORT   PORTD

#define TFT_DATA_PORT_DIR   DDRC
#define TFT_CTRL_PORT_DIR   DDRD

#define RST_PIN       PIN0  // CD pin
#define CS_PIN		  PIN1
#define RS_PIN        PIN2
#define WR_PIN        PIN3
#define RD_PIN  	  PIN4

#endif /* TFT_CFG_H_ */
