/*
 * =====================================================================================
 *
 *       Filename:  xil_oled.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/19/2015 02:00:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_OLED_H_
#define _XIL_OLED_H_

#include <../xlib/xil_gpio.h>
#include <../xlib/xil_spi.h>

/*****************************************
 * 【功 能 】:初始化引脚定义
 *
 * 【说 明 】:直接在这里改IO就可以了
 *      SCL:MIO12
 *      SDA:MIO10
 *      RST:MIO0
 *      D/C:MIO9
*******************************************/
void  LEDPIN_Init(void);   
void LED_Init(void);
void LED_CLS(void);
void LED_Set_Pos(uint8 x, uint8 y);
void LED_WrDat(uint8 data);   
void LED_P6x8Char(uint8 x,uint8 y,uint8 ch);
void LED_P6x8Str(uint8 x,uint8 y,uint8 ch[]);
void LED_P8x16Str(uint8 x,uint8 y,uint8 ch[]);
void LED_P14x16Str(uint8 x,uint8 y,uint8 ch[]);
void LED_PXx16MixStr(uint8 x,uint8 y,uint8 ch[]);
void LED_PrintBMP(uint8 x0,uint8 y0,uint8 x1,uint8 y1,uint8 bmp[]); 
void LED_Fill(uint8 dat);
void LED_PrintValueC(uint8 x,uint8 y,char data);
void LED_PrintValueI(uint8 x,uint8 y, int data);
void LED_PrintValueF(uint8 x,uint8 y, float data,uint8 num);
void LED_PrintEdge(void);
void LED_Cursor(uint8 cursor_column,uint8 cursor_row);
void LED_PrintLine(void);

#endif
