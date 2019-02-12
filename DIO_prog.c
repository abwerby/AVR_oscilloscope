/*
 * DIO.c
 *
 *  Created on: Sep 29, 2018
 *      Author: abood
 */

#include"LIB/STD_TYPES.h"
#include"LIB/BIT_MATH.h"
#include"DIO_reg.h"
#include"DIO_int.h"




void DIO_VidSetPortDirection(u8 PortId , u8 Value)
{
	switch(PortId)
	{
	case 0 :
		DDRA_Reg = Value ;
		break;
	case 1 :
		DDRB_Reg = Value ;
		break;
	case 2 :
		DDRC_Reg = Value ;
		break;
	case 3 :
		DDRD_Reg = Value ;
		break;
	}
}

void DIO_VidSetPortValue(u8 PortId , u8 Value)
{
	switch(PortId)
	{
	case 0 :
		PORTA_Reg = Value ;
		break;
	case 1 :
		PORTB_Reg = Value ;
		break;
	case 2 :
		PORTC_Reg = Value ;
		break;
	case 3 :
		PORTD_Reg = Value ;
		break;
	}
}

void DIO_VidSetPinDirection(u8 PortId , u8 Pin , u8 Value)
{
	switch(PortId)
	{
	case 0 :
		if(Value == 0xff)
		{
			SET_BIT(DDRA_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(DDRA_Reg,Pin);
		}
		break;
	case 1 :
		if(Value == 0xff)
		{
			SET_BIT(DDRB_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(DDRB_Reg,Pin);
		}
		break;
	case 2 :
		if(Value == 0xff)
		{
			SET_BIT(DDRC_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(DDRC_Reg,Pin);
		}
		break;
	case 3 :
		if(Value == 0xff)
		{
			SET_BIT(DDRD_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(DDRD_Reg,Pin);
		}
		break;
	}
}

void DIO_VidSetPinValue(u8 PortId , u8 Pin , u8 Value)
{
	switch(PortId)
	{
	case 0 :
		if(Value == 0xff)
		{
			SET_BIT(PORTA_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(PORTA_Reg,Pin);
		}
		break;
	case 1 :
		if(Value == 0xff)
		{
			SET_BIT(PORTB_Reg,Pin);
		}
		else if(Value == 0xff)
		{
			CLR_BIT(PORTB_Reg,Pin);
		}
		break;
	case 2 :
		if(Value == 0xff)
		{
			SET_BIT(PORTC_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(PORTC_Reg,Pin);
		}
		break;
	case 3 :
		if(Value == 0xff)
		{
			SET_BIT(PORTD_Reg,Pin);
		}
		else if(Value == 0)
		{
			CLR_BIT(PORTD_Reg,Pin);
		}
		break;
	}
}

u8 DIO_u8GetPortValue(u8 PortId)
{
	u8 Value ;
	switch(PortId)
	{
	case 0 :
		 Value = PINA_Reg ;
		break;
	case 1 :
		Value = PINB_Reg ;
		break;
	case 2 :
		 Value = PINC_Reg ;
		break;
	case 3 :
		 Value = PIND_Reg ;
		break;
	}
	return Value ;
}

u8 DIO_u8GetPinValue(u8 PortId , u8 PinNumber)
{
	u8 Value ;
	switch(PortId)
	{
	case 0 :
		 Value = GET_BIT(PINA_Reg,PinNumber) ;
		break;
	case 1 :
		Value = GET_BIT(PINB_Reg,PinNumber) ;
		break;
	case 2 :
		 Value = GET_BIT(PINC_Reg,PinNumber) ;
		break;
	case 3 :
		 Value = GET_BIT(PIND_Reg,PinNumber) ;
		break;
	}
	return Value ;
}
