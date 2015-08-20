/*
 * =====================================================================================
 *
 *       Filename:  xil_gpio.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 06:30:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#ifndef _XIL_GPIO_H_
#define _XIL_GPIO_H_

#include "xil_types.h"
#include "xil_io.h"

#define GPIO_CH1 1
#define GPIO_CH2 2

#define XIL_OUTPUT  0
#define XIL_INPUT   1

#define PS_GPIO_BASEADDR 0xE000A000


typedef struct _xil_gpio xil_gpio;
typedef struct _xil_gpio{
    int status;
    xil_io *xIO;
    void (*digitalWrite)(xil_gpio * const me, u8 ch, u8 pin, boolean value);
    void (*modeWrite)(xil_gpio * const me, u8 ch, u8 pin, boolean value);
    boolean (*digitalRead)(xil_gpio * const me, u8 ch, u8 pin);
    boolean (*modeRead)(xil_gpio * const me, u8 ch, u8 pin);
    
    void (*digitalChipWrite)(xil_gpio * const me, u8 ch, u32 value);
    void (*modeChipWrite)(xil_gpio * const me, u8 ch, u32 value);
    u32 (*digitalChipRead)(xil_gpio * const me, u8 ch);
    u32 (*modeChipRead)(xil_gpio * const me, u8 ch);
}xil_gpio;

xil_gpio *XilGpioCreate(u32 BaseAddress);
void XilGpioDestroy(xil_gpio *me);

#endif
