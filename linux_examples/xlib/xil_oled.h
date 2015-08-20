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

#include "../xlib/xil_types.h"
#include "../xlib/xil_gpio.h"
#include "../xlib/xil_spi.h"

/*****************************************
 * 【功 能 】:初始化引脚定义
 *
 * 【说 明 】:直接在这里改IO就可以了
 *      SCL:MIO12
 *      SDA:MIO10
 *      RST:MIO0
 *      D/C:MIO9
*******************************************/
xil_gpio *oled_gpio;

#define OLED_USE_SPI

#ifdef OLED_USE_SPI
xil_spi *oled_SPI;
#define OLED_RST_PIN    0
#define OLED_DC_PIN     9
#define OLED_SPI_DEVNAME "/dev/spidev32766.0"
#else
#define AXI_GPIO_BASEADDR   0x41220000
#define OLED_SCL_PIN            3
#define OLED_SDA_PIN            2
#define OLED_RST_PIN            1
#define OLED_DC_PIN             0
#endif

void  LEDPIN_Init(void);   
void LED_Init(void);
void LED_Uninit(void);
void LED_CLS(void);
void LED_Set_Pos(u8 x, u8 y);
void LED_WrDat(u8 data);   
void LED_P6x8Char(u8 x,u8 y,u8 ch);
void LED_P6x8Str(u8 x,u8 y,u8 ch[]);
void LED_P8x16Str(u8 x,u8 y,u8 ch[]);
void LED_P14x16Str(u8 x,u8 y,u8 ch[]);
void LED_PXx16MixStr(u8 x,u8 y,u8 ch[]);
void LED_PrintBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 bmp[]); 
void LED_Fill(u8 dat);
void LED_PrintValueC(u8 x,u8 y,char data);
void LED_PrintValueI(u8 x,u8 y, int data);
void LED_PrintValueF(u8 x,u8 y, float data,u8 num);
void LED_PrintEdge(void);
void LED_Cursor(u8 cursor_column,u8 cursor_row);
void LED_PrintLine(void);

#endif
