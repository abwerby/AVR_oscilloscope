/*
 * TFT_Interface.h
 *
 *  Created on: Jan 23, 2019
 *      Author: abdelrhamn werby
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

/************************************************************
 *
 *  CONTROL FUNCTIONS
 *
 ************************************************************/



void TFT_Init();
void TFT_Reset();
void TFT_Clear(u16 color);
void TFT_Set_Rotation(u8 rotation);

/************************************************************
 *
 *  DRAW FUNCTIONS
 *
 ************************************************************/


void TFT_Draw_Line(s16 x0, s16 y0,s16 x1, s16 y1,u16 color);
void TFT_Draw_Circle(s16 x0, s16 y0, s16 r,u16 color);
void TFT_DrawRect(s16 x, s16 y,  s16 w, s16 h,  u16 color);
void TFT_DrawFastVLine(s16 x, s16 y,s16 h, u16 color);
void TFT_DrawFastHLine(s16 x, s16 y,s16 w, u16 color);
void TFT_fillRect(s16 x, s16 y, s16 w, s16 h,u16 color);
void TFT_fillScreen(u16 color);
void TFT_fillCircle(s16 x0, s16 y0, s16 r,u16 color);
void TFT_Draw_Point(s16 x0, s16 y0 ,u16 color);




/************************************************************
 *
 * TEXT PRINT FUNCTIONS
 *
 ************************************************************/


void TFT_SetCursor(s16 x, s16 y);
void TFT_SetTextSize(u8 s);
void TFT_SetTextColor(u16 c, u16 b);
void TFT_Print_String(s8 *string , u8 TFT_STRING_MODE);
void TFT_Print_Number(long  Number, u8 TFT_STRING_MODE);





#define TFT_STRING_MODE_NO_BACKGROUND	0x01
#define TFT_STRING_MODE_BACKGROUND	0x00


/************************************************************
 *
 *  COLORS
 *
 ************************************************************/


#define ILI9486_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9486_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9486_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9486_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9486_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9486_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9486_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9486_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9486_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9486_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9486_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9486_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9486_RED         0xF800      /* 255,   0,   0 */
#define ILI9486_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9486_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9486_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9486_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9486_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9486_PINK        0xF81F

/************************************************************
 *
 *  ORINTIONS
 *
 ************************************************************/


#define TFT_PORTRAIT       0
#define TFT_LANDSCAPE      1
#define TFT_PORTRAIT_REV   2
#define TFT_LANDSCAPE_REV  3



#endif /* TFT_INTERFACE_H_ */
