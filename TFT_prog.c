/*
 * TFT_prog.c
 *
 *  Created on: Jan 23, 2019
 *      Author: ab_werby
 */

#include "avr/pgmspace.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "TFT_Interface.h"
#include "TFT_cfg.h"
//#include "DIO_reg.h"
#include "avr/io.h"
#include "TFT_Privte.h"
#include "TFT_Fonts.h"
#include "avr/delay.h"


void TFT_Init()
{
	TFT_GPIO_Init();
	TFT_Reset();

	TFT_Write_Cmd_Byte(0x11); // Sleep out, also SW reset
	_delay_ms(60);

	TFT_Write_Cmd_Byte(0x3A);
	TFT_Write_Data_Byte(0x55);

	TFT_Write_Cmd_Byte(0xC2);
	TFT_Write_Data_Byte(0x44);

	TFT_Write_Cmd_Byte(0xC5);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0xE0);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x1F);
	TFT_Write_Data_Byte(0x1C);
	TFT_Write_Data_Byte(0x0C);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x08);
	TFT_Write_Data_Byte(0x48);
	TFT_Write_Data_Byte(0x98);
	TFT_Write_Data_Byte(0x37);
	TFT_Write_Data_Byte(0x0A);
	TFT_Write_Data_Byte(0x13);
	TFT_Write_Data_Byte(0x04);
	TFT_Write_Data_Byte(0x11);
	TFT_Write_Data_Byte(0x0D);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0xE1);
	TFT_Write_Data_Byte(0x0F);
	TFT_Write_Data_Byte(0x32);
	TFT_Write_Data_Byte(0x2E);
	TFT_Write_Data_Byte(0x0B);
	TFT_Write_Data_Byte(0x0D);
	TFT_Write_Data_Byte(0x05);
	TFT_Write_Data_Byte(0x47);
	TFT_Write_Data_Byte(0x75);
	TFT_Write_Data_Byte(0x37);
	TFT_Write_Data_Byte(0x06);
	TFT_Write_Data_Byte(0x10);
	TFT_Write_Data_Byte(0x03);
	TFT_Write_Data_Byte(0x24);
	TFT_Write_Data_Byte(0x20);
	TFT_Write_Data_Byte(0x00);

	TFT_Write_Cmd_Byte(0x20);                     // display inversion OFF

	TFT_Write_Cmd_Byte(0x36);
	TFT_Write_Data_Byte(0x48);

	TFT_Write_Cmd_Byte(0x29);                     // display on
	_delay_ms(60);

	TFT_Set_Rotation(TFT_LANDSCAPE);


}

/*
void Write_Byte(u8 data)
{
	// WRITE DATA
	TFT_DATA_PORT=data;

	// WR_ACTIVE
	CLR_BIT(TFT_CTRL_PORT,WR_PIN);

	//_delay_us(50);

	// WR_IDLE
	SET_BIT(TFT_CTRL_PORT,WR_PIN);

}
*/


void TFT_Write_Data_Byte(u8 data)
{
	/* CS_ACTIVE */
	CLR_BIT(TFT_CTRL_PORT,CS_PIN);

	/* CD/RS DATA */
	SET_BIT(TFT_CTRL_PORT,RS_PIN);

	Write_Byte(data);

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,CS_PIN);
}

void TFT_Write_Cmd_Byte(u8 cmd)
{
	/* CS_ACTIVE */
	CLR_BIT(TFT_CTRL_PORT,CS_PIN);

	/* CD/RS COMMAND */
	CLR_BIT(TFT_CTRL_PORT,RS_PIN);

	Write_Byte(cmd);

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,CS_PIN);


}

void TFT_Write_Data_Word(u16 data)
{
	/* CS_ACTIVE */
	CLR_BIT(TFT_CTRL_PORT,CS_PIN);

	/* CD/RS DATA */
	SET_BIT(TFT_CTRL_PORT,RS_PIN);

	Write_Byte(data >> 8 );
	Write_Byte(data & 0xff );

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,CS_PIN);

}

void TFT_Write_Cmd_Word(u16 cmd)
{

	/* CS_ACTIVE */
	CLR_BIT(TFT_CTRL_PORT,CS_PIN);

	/* CD/RS COMMAND */
	CLR_BIT(TFT_CTRL_PORT,RS_PIN);

	Write_Byte(cmd >> 8 );
	Write_Byte(cmd & 0xff );

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,CS_PIN);
}

void TFT_Write_Cmd_Data(u16 cmd, u16 data) {
	TFT_Write_Cmd_Byte(cmd);
	TFT_Write_Data_Word(data);
}

void TFT_GPIO_Init()
{
	/* SET CONTROL PINS OUTPUT */
	SET_BIT(TFT_CTRL_PORT_DIR,WR_PIN);
	SET_BIT(TFT_CTRL_PORT_DIR,RS_PIN);
	SET_BIT(TFT_CTRL_PORT_DIR,CS_PIN);
	SET_BIT(TFT_CTRL_PORT_DIR,RD_PIN);
	SET_BIT(TFT_CTRL_PORT_DIR,RST_PIN);


	/* SET DATA PINS OUTPUT */
	TFT_DATA_PORT_DIR = 0xFF ;
}

void TFT_Reset()
{

	/* CS_IDLE */
	SET_BIT(TFT_CTRL_PORT,CS_PIN);

	/* RD_IDLE */
	SET_BIT(TFT_CTRL_PORT,RD_PIN);

	/* WR_IDLE */
	SET_BIT(TFT_CTRL_PORT,WR_PIN);

	/* RESET_IDLE */
	SET_BIT(TFT_CTRL_PORT,RST_PIN);

	_delay_ms(50);

	/* RESET_IDLE */
	CLR_BIT(TFT_CTRL_PORT,RST_PIN);

	_delay_ms(100);

	/* RESET_IDLE */
	SET_BIT(TFT_CTRL_PORT,RST_PIN);

	_delay_ms(100);

}

void TFT_Write_Data_Cmd(u16 cmd, u16 data)
{
	TFT_Write_Cmd_Byte(cmd);
	TFT_Write_Data_Word(data);
}


void TFT_Write_Cmd_ParamN(u8 cmd, s8 N, u8 * block)
{
	TFT_Write_Cmd_Byte(cmd);
	while (N-- > 0)
	{
		u8 Z = *block++;
		TFT_Write_Data_Byte(Z);;
	}
}

void TFT_Write_Cmd_Param4(u8 cmd, u8 d1, u8 d2, u8 d3, u8 d4)
{
	u8 d[4];
	d[0] = d1, d[1] = d2, d[2] = d3, d[3] = d4;
	TFT_Write_Cmd_ParamN(cmd, 4, d);
}


void TFT_Clear(u16 color)
{
	u16 i,j;

	TFT_SetAddrWindow(0,0,tft_W-1,tft_H-1);
	TFT_Write_Cmd_Byte(TFT_RAMWR);
	for(i=0;i<tft_W;i++)
	{
		for (j=0;j<tft_H;j++)
		{
			TFT_Write_Data_Word(color);
		}
	}
}

void TFT_Scroll_Vertical(s16 top, s16 scrollines, s16 offset)
{
	s16 bfa = tft_H - top - scrollines;  // bottom fixed area
	s16 vsp;
	s16 sea = top;
	vsp = top + offset; // vertical start position

	if (offset < 0)
	{
		vsp += scrollines;     //keep in unsigned range
	}
	sea = top + scrollines - 1;



        u8 d[6];           // for multi-byte parameters

        d[0] = top >> 8;        //TFA
        d[1] = top;
        d[2] = scrollines >> 8; //VSA
        d[3] = scrollines;
        d[4] = bfa >> 8;        //BFA
        d[5] = bfa;
        TFT_Write_Cmd_ParamN(0x33, 6, d);

		d[0] = vsp >> 8;        //VSP
        d[1] = vsp;
        TFT_Write_Cmd_ParamN(0x37, 2, d);

}

void drawPixel(u16 x, u16 y, u16 color)
{


	if (x < 0 || y < 0 || x >= tft_W || y >= tft_H)
	{
		return;
	}


	TFT_Write_Cmd_Param4(TFT_CASET, x >> 8, x, x >> 8, x);
	TFT_Write_Cmd_Param4(TFT_PASET, y >> 8, y, y >> 8, y);

	TFT_Write_Cmd_Data(TFT_RAMWR,color);
}






void TFT_Draw_Line(s16 x1, s16 y1, s16 x2, s16 y2, u16 color) {

	s16 i;
	s16 dx,dy;
	s16 sx,sy;
	s16 E;

	/* distance between two points */
	if(x2 > x1)
	{
		dx = x2 - x1 ;
	}
	else
	{
		dx = x1 - x2 ;
	}

	if(y2 > y1)
	{
		dy = y2 - y1 ;
	}
	else
	{
		dy = y1 - y2 ;
	}



	/* direction of two point */

	if(x2 > x1)
	{
		sx = 1 ;
	}
	else
	{
		sx = -1 ;
	}

	if(y2 > y1)
	{
		sy = 1 ;
	}
	else
	{
		sy = -1;
	}


	if (y1 == y2) {
		if (x2 > x1) {
			TFT_DrawFastHLine(x1, y1, x2 - x1 + 1, color);
		} else {
			TFT_DrawFastHLine(x2, y1, x1 - x2 + 1, color);
		}
		return;
	} else if (x1 == x2) {
		if (y2 > y1) {
			TFT_DrawFastVLine(x1, y1, y2 - y1 + 1, color);
		} else {
			TFT_DrawFastVLine(x1, y2, y1 - y2 + 1, color);
		}
		return;
	}

	/* inclination < 1 */
	if ( dx > dy ) {
		E = -dx;
		for ( i = 0 ; i <= dx ; i++ ) {
			drawPixel( x1, y1, color );
			x1 += sx;
			E += 2 * dy;
			if ( E >= 0 ) {
				y1 += sy;
				E -= 2 * dx;
			}
		}
		/* inclination >= 1 */
	} else {
		E = -dy;
		for ( i = 0 ; i <= dy ; i++ ) {
			drawPixel( x1, y1, color );
			y1 += sy;
			E += 2 * dx;
			if ( E >= 0 ) {
				x1 += sx;
				E -= 2 * dy;
			}
		}
	}
}



void TFT_Draw_Circle(s16 x0, s16 y0, s16 r,u16 color)
{
	s16 f = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x = 0;
	s16 y = r;

	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x;

		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);
	}
}


void TFT_fillCircle(s16 x0, s16 y0, s16 r,u16 color)
{
	TFT_DrawFastVLine(x0, y0-r, 2*r+1, color);
	TFT_fillCircleHelper(x0, y0, r, 3, 0, color);
}

void TFT_Draw_Point(s16 x0, s16 y0 ,u16 color)
{
	s16 r = 1 ;
	TFT_DrawFastVLine(x0, y0-r, 2*r+1, color);
	TFT_fillCircleHelper(x0, y0, r, 3, 0, color);
}

void TFT_fillCircleHelper(s16 x0, s16 y0, s16 r,u8 cornername, s16 delta, u16 color)
{

	s16 f     = 1 - r;
	s16 ddF_x = 1;
	s16 ddF_y = -2 * r;
	s16 x     = 0;
	s16 y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1) {
			TFT_DrawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			TFT_DrawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) {
			TFT_DrawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			TFT_DrawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

void TFT_DrawRect(s16 x, s16 y,  s16 w, s16 h,  u16 color)
{
	TFT_DrawFastHLine(x, y, w, color);
	TFT_DrawFastHLine(x, y+h-1, w, color);
	TFT_DrawFastVLine(x, y, h, color);
	TFT_DrawFastVLine(x+w-1, y, h, color);
}

void TFT_DrawFastVLine(s16 x, s16 y,s16 h, u16 color)
{
	if ((x >= tft_W) || (y >= tft_H || h < 1))
	{
		return;
	}
	if ((y + h - 1) >= tft_H)
	{
		h = tft_H - y;
	}

	TFT_fillRect(x, y, 1, h, color);
}

void TFT_DrawFastHLine(s16 x, s16 y,s16 w, u16 color)
{
	if ((x >= tft_W) || (y >= tft_H || w < 1))
	{
		return;
	}
	if ((x + w - 1) >=tft_W)
	{
		w =tft_W - x;
	}
	TFT_fillRect(x, y, w, 1, color);
}

void TFT_fillScreen(u16 color)
{
	TFT_fillRect(0, 0, tft_W, tft_H, color);
}

void TFT_SetAddrWindow(s16 x, s16 y, s16 x1, s16 y1)
{
	TFT_Write_Cmd_Param4(TFT_CASET, x >> 8, x, x1 >> 8, x1);
	TFT_Write_Cmd_Param4(TFT_PASET, y >> 8, y, y1 >> 8, y1);
}


void TFT_fillRect(s16 x, s16 y, s16 w, s16 h, u16 color)
{
	s16 end;
	if (w < 0) {
		w = -w;
		x -= w;
	}                           //+ve w
	end = x + w;
	if (x < 0)
		x = 0;
	if (end > tft_W)
		end = tft_W;
	w = end - x;
	if (h < 0) {
		h = -h;
		y -= h;
	}                           //+ve h
	end = y + h;
	if (y < 0)
		y = 0;
	if (end > tft_H)
		end = tft_H;
	h = end - y;

	TFT_SetAddrWindow(x, y, x + w - 1, y + h - 1);
	TFT_Write_Cmd_Byte(TFT_RAMWR);
	if (h > w) {
		end = h;
		h = w;
		w = end;
	}
	while (h-- > 0) {
		end = w;
		do {
			TFT_Write_Data_Word(color);
		} while (--end != 0);
	}

}


void TFT_Print_Char14x24(u16 x,u16 y,u8 data ,u8 mode)
{


	if((x>tft_W-14)||(y>tft_H-24)) return;
	u8 i,j,k,temp;
	TFT_SetAddrWindow(x,y,x+16-1,y+24-1);
	for(i=0;i<24/8;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<14;k++)
			{
				temp = pgm_read_byte(&(Consolas14x24[(data-' ')*(24/8)*14+k*(24/8)+i]));      // temp=Consolas14x24[(data-' ')*(24/8)*14+k*(24/8)+i];
				if(mode==TFT_STRING_MODE_BACKGROUND)
				{
					if(temp&(0x01<<j))
					{
						TFT_Write_Data_Word(POINT_COLOR);
					}
					else
					{
						TFT_Write_Data_Word(BACK_COLOR);
					}
				}
				else
				{
					if(temp&(0x01<<j))
					{
						drawPixel(x+k,y+(8*i+j),POINT_COLOR);
					}
				}
			}
		}
	}
}


void TFT_Print_Char18x32(u16 x,u16 y,u8 data,u8 mode)
{
	if((x>tft_W-18)||(y>tft_H-32)) return;
	u8 i,j,k,temp;
	TFT_SetAddrWindow(x,y,x+18-1,y+32-1);
	for(i=0;i<32/8;i++)
	{
		for(j=0;j<8;j++)
		{
			for(k=0;k<18;k++)
			{
				temp = pgm_read_byte(&(Consolas18x32[(data-' ')*(32/8)*18+k*(32/8)+i]));          //temp=Consolas18x32[(data-' ')*(32/8)*18+k*(32/8)+i];
				if(mode==TFT_STRING_MODE_BACKGROUND)
				{
					if(temp&(0x01<<j))
					{
						TFT_Write_Data_Word(POINT_COLOR);
					}
					else
					{
						TFT_Write_Data_Word(BACK_COLOR);
					}
				}
				else
				{
					if(temp&(0x01<<j))
					{
						drawPixel(x+k,y+(8*i+j),POINT_COLOR);
					}
				}
			}
		}
	}
}


void TFT_Print_Char8x16(u16 x,u16 y,u8 num,u8 mode)
{
	u8 temp;
	u8 pos,t;
	//uint16_t x0=x;
	u16 colortemp=POINT_COLOR;
	if(x>TFT_WIDTH-8||y>TFT_HEIGHT-16)return;
	num=num-' ';
	TFT_SetAddrWindow(x,y,y+16-1, x+8-1);
	if(!mode)
	{
		for(pos=0;pos<16;pos++)
		{
			temp = pgm_read_byte(&(asc2_1608[(u16)num*16+pos]));       // temp=asc2_1608[(u16)num*16+pos];
			for(t=0;t<8;t++)
			{
				if(temp&0x01)
				{
					POINT_COLOR=colortemp;
				}
				else
				{
					POINT_COLOR=BACK_COLOR;
				}
				TFT_Write_Data_Word(POINT_COLOR);
				temp>>=1;
			}
		}
	}
	else
	{
		for(pos=0;pos<16;pos++)
		{
			temp = pgm_read_byte(&(asc2_1608[(u16)num*16+pos]));       //temp=asc2_1608[(u16)num*16+pos];
			for(t=0;t<8;t++)
			{
				if(temp&0x01)drawPixel(x+t,y+pos,POINT_COLOR);
				temp>>=1;
			}
		}
	}
	POINT_COLOR=colortemp;
}




void TFT_SetCursor(s16 x, s16 y)
{
	cursor_x = y;
	cursor_y = x;
}

void TFT_SetTextSize(u8 s)
{
	textsize = s ;
}


void TFT_SetTextColor(u16 c, u16 b)
{
	POINT_COLOR   = c;
	BACK_COLOR = b;
}


void TFT_Set_Rotation(u8 rotation)
{
#define RGB 1
#define BGR 0

	TFT_Write_Cmd_Byte(0x36);

	if(rotation == 0)
	{
		TFT_Write_Data_Byte(0x48);
		tft_W = TFT_WIDTH;
		tft_H = TFT_HEIGHT;
	}

	if(rotation == 1)
	{
		TFT_Write_Data_Byte(0x28);
		tft_W = TFT_HEIGHT;
		tft_H = TFT_WIDTH;
	}

	if(rotation == 2)
	{
		TFT_Write_Data_Byte(0x98);
		tft_W =TFT_WIDTH;
		tft_H = TFT_HEIGHT;
	}

	if(rotation == 3)
	{
		TFT_Write_Data_Byte(0xF8);
		tft_W = TFT_HEIGHT;
		tft_H =TFT_WIDTH;
	}

}

void TFT_Print_String18x32(s8 *string,u8 TFT_STRING_MODE)
{
	u8 i=0;
	u8 font_w=18;
	u8 font_h=32;

	while(*(string+i)!='\0')
	{

		if(*(string+i)==0)
		{
			return;
		}

		if(*(string+i)=='\n')
		{
			cursor_x+=font_h;
			cursor_y=0;
			string++;
		}

		if(cursor_y>tft_W-font_w)
		{
			cursor_y=0;cursor_x+=font_h;
		}

		if(cursor_x>tft_H-font_h)
		{
			cursor_x=cursor_y=0;
		}

		TFT_Print_Char18x32(cursor_y,cursor_x,*(string+i),TFT_STRING_MODE);
		cursor_y+=font_w;
		i++;
	}
}


void TFT_Print_String14x24(s8 *string,u8 TFT_STRING_MODE)
{
	u8 i=0;
	u8 font_w=14;
	u8 font_h=24;

	while(*(string+i)!='\0')
	{

		if(*(string+i)==0)
		{
			return;
		}

		if(*(string+i)=='\n')
		{
			cursor_x+=font_h;
			cursor_y=0;
			string++;
		}

		if(cursor_y>tft_W-font_w)
		{
			cursor_y=0;cursor_x+=font_h;
		}

		if(cursor_x>tft_H-font_h)
		{
			cursor_x=cursor_y=0;
		}

		TFT_Print_Char14x24(cursor_y,cursor_x,*(string+i),TFT_STRING_MODE);
		cursor_y+=font_w;
		i++;
	}
}

void TFT_Print_String8x16(s8 *string,u8 TFT_STRING_MODE)
{
	u8 i=0;
	u8 font_w=8;
	u8 font_h=16;

	while(*(string+i)!='\0')
	{

		if(*(string+i)==0)
		{
			return;
		}

		if(*(string+i)=='\n')
		{
			cursor_x+=font_h;
			cursor_y=0;
			string++;
		}

		if(cursor_y>tft_W-font_w)
		{
			cursor_y=0;cursor_x+=font_h;
		}

		if(cursor_x>tft_H-font_h)
		{
			cursor_x=cursor_y=0;
		}

		TFT_Print_Char8x16(cursor_y,cursor_x,*(string+i),TFT_STRING_MODE);
		cursor_y+=font_w;
		i++;
	}
}

void TFT_Print_String(s8 *string , u8 TFT_STRING_MODE)
{
	switch(textsize)
	{
	case 1 : TFT_Print_String8x16(string, TFT_STRING_MODE);
	break;
	case 2 : TFT_Print_String14x24(string, TFT_STRING_MODE);
	break;
	case 3 : TFT_Print_String18x32(string, TFT_STRING_MODE);
	break;

	}
}


void TFT_Print_Number(long  Number, u8 TFT_STRING_MODE)
{

	long Temp =1;

	if (Number <= 0)
	{
		switch(textsize)
		{
		case 1 : TFT_Print_Char8x16(cursor_y,cursor_x,'0', TFT_STRING_MODE);  cursor_y+=8;
		break;
		case 2 : TFT_Print_Char14x24(cursor_y,cursor_x,'0', TFT_STRING_MODE); cursor_y+=14;
		break;
		case 3 : TFT_Print_Char18x32(cursor_y,cursor_x,'0', TFT_STRING_MODE); cursor_y+=18;
		break;

		}
	}
	else
	{
		while (Number!=0)
		{
			u8 Reminder = Number % 10;
			Number = Number / 10 ;
			Temp = Temp * 10 + Reminder ;
		}
		while (Temp != 1)
		{
			u8 Reminder2 = Temp % 10 ;

			switch(textsize)
			{
			case 1 : TFT_Print_Char8x16(cursor_y,cursor_x,Reminder2+48, TFT_STRING_MODE);   cursor_y+=8;
			break;
			case 2 : TFT_Print_Char14x24(cursor_y,cursor_x,Reminder2+48, TFT_STRING_MODE);  cursor_y+=14;
			break;
			case 3 : TFT_Print_Char18x32(cursor_y,cursor_x,Reminder2+48, TFT_STRING_MODE);  cursor_y+=18;
			break;

			}
			Temp = Temp / 10 ;
		}
	}


}

