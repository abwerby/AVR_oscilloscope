/*
 * TFT_Privte.h
 *
 *  Created on: Jan 23, 2019
 *      Author: abood
 */

#ifndef TFT_PRIVTE_H_
#define TFT_PRIVTE_H_


/*********************************************************************
 *
 *  PRIVTE FUNCTION USER CANNOT USE IT
 *
 ***********************************************************************/


void drawPixel(u16 x, u16 y, u16 color);
void TFT_GPIO_Init();
void Write_Byte(u8 data);
void TFT_Write_Data_Byte(u8 data);
void TFT_Write_Cmd_Byte(u8 cmd);
void TFT_Wrte_Data_Word(u16 data);
void TFT_Write_Cmd_Word(u16 data);


void TFT_SetAddrWindow(s16 x, s16 y, s16 x1, s16 y1);
void TFT_fillCircleHelper(s16 x0, s16 y0, s16 r,u8 cornername, s16 delta, u16 color);


void TFT_Print_Char14x24(u16 x,u16 y,u8 data ,u8 mode);
void TFT_Print_Char18x32(u16 x,u16 y,u8 data,u8 mode);
void TFT_Print_Char8x16(u16 x,u16 y,u8 num,u8 mode);
void TFT_Print_String18x32(s8 *string,u8 TFT_STRING_MODE);
void TFT_Print_String14x24(s8 *string,u8 TFT_STRING_MODE);
void TFT_Print_String8x16(s8 *string,u8 TFT_STRING_MODE);


#define Write_Byte(data){ TFT_DATA_PORT=data; CLR_BIT(TFT_CTRL_PORT,WR_PIN); SET_BIT(TFT_CTRL_PORT,WR_PIN);}


/*********************************************************************
 *
 *  SCREEN SIZE
 *
 **********************************************************************/

#define TFT_WIDTH  320
#define TFT_HEIGHT 480


/*********************************************************************
 *
 *  GLOBALE VARIBLE
 *
 **********************************************************************/



u8 font_width, font_height;
u8 font_offset;
u8 *font_addr;

u16 tft_W = TFT_WIDTH;
u16 tft_H = TFT_HEIGHT;

s16   _width, _height, cursor_x, cursor_y , color ;
u16   POINT_COLOR, BACK_COLOR;
u8    textsize, rotation;



/*********************************************************************
 *
 *  ORINTIONS OF SCREEN COMMAND
 *
 ***********************************************************************/

#define PORTRAIT       0x48
#define LANDSCAPE      0x28
#define PORTRAIT_REV   0x98
#define LANDSCAPE_REV  0xF4

/*********************************************************************
 *
 *   SCREEN COMMAND
 *
 ***********************************************************************/

#define TFT_NOP     0x00
#define TFT_SWRST   0x01
#define TFT_CASET   0x2A
#define TFT_PASET   0x2B
#define TFT_RAMWR   0x2C
#define TFT_RAMRD   0x2E
#define TFT_MADCTL  0x36
#define TFT_MAD_MY  0x80
#define TFT_MAD_MX  0x40
#define TFT_MAD_MV  0x20
#define TFT_MAD_ML  0x10
#define TFT_MAD_BGR 0x08
#define TFT_MAD_MH  0x04
#define TFT_MAD_SS  0x02
#define TFT_MAD_GS  0x01
#define TFT_MAD_RGB 0x00
#define TFT_INVOFF  0x20
#define TFT_INVON   0x21


#endif /* TFT_PRIVTE_H_ */
