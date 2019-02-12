/*
 * main.c
 *
 *  Created on: Jan 23, 2019
 *      Author: abdelrhman werby
 */

#define F_CPU 12000000U
#include "avr/pgmspace.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "TFT_Interface.h"
#include "avr/delay.h"
#include "DIO_int.h"
#include "ADC_MCP_int.h"
#include "ADC_int.h"

#define Mega 1000000
#define S_Time 19	// SAMPLE TIME FOR 52.63 KHZ SAMPLE RATE
#define FFT_N 800	// NUMBER OF SAMPLE

/*
 *  GLOAPLE VARIBLE
 */

u16 maximum , manimum , Avg ;
u16 P_Time = 0 ;
u8 location_min , location_max ;
u16 volt[FFT_N]  ;

/*
 *
 *
 *  FUNCTIONS PROTOTYPE
 *
 *
 */

void Net();
long map(long x, long in_min, long in_max, long out_min, long out_max);
void freq(u16 array[]);
void min( u16 array[]);
void max( u16 array[]);


int main()
{

	/*
	 * INIT ALL HARDWARE
	 */
	TFT_Init();
	Init_ADC_MCP();
	ADC_vidInit();

	TFT_fillScreen(ILI9486_BLACK); // FILL SCREEN WITH BLACK

	/*
	 * DRAW NET LINES
	 */

	TFT_DrawFastHLine(0,160,380,ILI9486_WHITE);
	TFT_DrawFastVLine(190,50,220,ILI9486_WHITE);
	TFT_DrawFastHLine(0,270,380,ILI9486_GREEN);
	TFT_DrawFastHLine(0,50,380,ILI9486_GREEN);
	TFT_DrawFastVLine(380,0,320,ILI9486_GREEN);




	TFT_SetTextSize(2);
	TFT_SetCursor(388,2);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("TimDiv",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(3);
	TFT_SetCursor(80,2);
	TFT_SetTextColor(ILI9486_GREENYELLOW,ILI9486_BLACK);
	TFT_Print_String("Oscilloscope",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(2);
	TFT_SetCursor(2,285);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("FREQ =",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(2);
	TFT_SetCursor(195,285);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("T =",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(2);
	TFT_SetCursor(388,85);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("AVG",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(2);
	TFT_SetCursor(388,165);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("MAX",TFT_STRING_MODE_NO_BACKGROUND);


	TFT_SetTextSize(2);
	TFT_SetCursor(388,245);
	TFT_SetTextColor(ILI9486_GREEN,ILI9486_BLACK);
	TFT_Print_String("MIN",TFT_STRING_MODE_NO_BACKGROUND);



	while(1)
	{


		u16 TimeDiv;


		/*
		 * READ SIGNAL FROM MCP3001
		 *
		 */

		for(u16 t = 0 ; t < FFT_N ; t++)
		{
			volt[t] = Read_ADC_MCP();
		}

		for(u16 t = 0 ; t < FFT_N ; t++)
		{
			volt[t] = map(volt[t],0,1024,0,5000);
		}

		/*
		 *  CAULC MAX PEAK AND MIN PEAK AND AVG AND FREQUENCY OF INPUT SIGNAL
		 */

		maximum = 0 ;
		manimum = 0 ;
		max(volt);
		min(volt);
		Avg = (maximum+manimum)/2 ;
		freq(volt);

		// Y AXIS SCALE
		for(u16 t = 0 ; t < FFT_N  ; t++)
		{
			volt[t] = map(volt[t],0,4999,250,75);
		}


		/*
		 * DRAW SIGNAL AND SCALE IT FOR SCREEN
		 */

		u16 i = 0 ;
		for(u16 t = 1 ; t < FFT_N ; t++)
		{
			i = map(t,0,799,0,359);

			if(i * TimeDiv > 356)
			{
				break;
			}

			TFT_Draw_Line((i-1)*TimeDiv,volt[t-1],i*TimeDiv,volt[t],ILI9486_RED);
			_delay_ms(5);

		}



		/*
		 * CLEAR SCREEN BY REDRAW SIGNAL IN BLACK
		 */



		i = 0 ;
		for(u16 t = 1 ; t < FFT_N ; t++)
		{
			i = map(t,0,799,0,359);

			if(i * TimeDiv > 356)
			{
				break;
			}

			TFT_Draw_Line((i-1)*TimeDiv,volt[t-1],i*TimeDiv,volt[t],ILI9486_BLACK);
		}

		/*
		 * REDRAW NET LINES
		 */

		TFT_DrawFastHLine(0,160,380,ILI9486_WHITE);
		TFT_DrawFastVLine(190,50,220,ILI9486_WHITE);


		TFT_SetTextSize(2);
		TFT_SetCursor(388,195);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(388,195,100,20,ILI9486_BLACK);
		TFT_Print_Number(maximum,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String("mV",1);

		TFT_SetTextSize(2);
		TFT_SetCursor(388,275);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(388,275,100,20,ILI9486_BLACK);
		TFT_Print_Number(manimum,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String("mV",1);

		TFT_SetTextSize(2);
		TFT_SetCursor(388,115);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(388,115,100,20,ILI9486_BLACK);
		TFT_Print_Number(Avg,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String("mV",1);

		TFT_SetTextSize(2);
		TFT_SetCursor(95,285);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(95,285,100,20,ILI9486_BLACK);
		TFT_Print_Number(1000000/P_Time,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String(" HZ",1);

		TFT_SetTextSize(2);
		TFT_SetCursor(250,285);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(250,285,100,20,ILI9486_BLACK);
		TFT_Print_Number(P_Time,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String(" uS",1);



		// READ TIMEDIV VALUE FROM POT
		TimeDiv = ADC_u16GetAdValue(ADC_CHANNEL_1) ;
		TimeDiv = map(TimeDiv,0,1023,1,10);

		TFT_SetTextSize(2);
		TFT_SetCursor(388,32);
		TFT_SetTextColor(ILI9486_BLUE,ILI9486_BLACK);
		TFT_fillRect(388,32,100,20,ILI9486_BLACK);
		TFT_Print_Number(TimeDiv,1);
		TFT_SetTextColor(ILI9486_PURPLE,ILI9486_BLACK);
		TFT_Print_String(" uS",1);


	}

	return 0 ;
}



/*
 *
 *
 *  FUNCTIONS DEFNTIONS
 *
 *
 */

void max (u16 array[])
{
	for (int c = 1; c < FFT_N; c++)
	{
		if (array[c] > maximum)
		{
			maximum  = array[c];
			location_max = c+1;
		}
	}
}

void min ( u16 array[])
{
	for (int c = 1; c < FFT_N ; c++)
	{
		if (array[c] < manimum)
		{
			manimum  = array[c];
			location_min = c+1;
		}
	}
}


void freq(u16 array[])
{
	u8 cut_Loc_1 , cut_Loc_2 , k = 0 ;
	for(u16 i = 1 ; i < FFT_N ; i++)
	{
		if(array[i-1] < Avg && array[i] > Avg)
		{
			if(k == 0)
			{
				cut_Loc_1 = i ;
				k = 1 ;
			}
			else
			{
				cut_Loc_2 = i ;
				k = 0 ;
				P_Time = (cut_Loc_2 - cut_Loc_1) * S_Time ;
				break ;
			}

		}


	}



}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Net()
{
	for(u16 i = 75 ; i <= 270 ; i = i+20)
	{
		TFT_DrawFastHLine(0,i,380,ILI9486_OLIVE);
	}

	for(u16 j = 20 ; j <= 380 ; j = j+20)
	{
		TFT_DrawFastVLine(j,75,245,ILI9486_OLIVE);
	}

}

