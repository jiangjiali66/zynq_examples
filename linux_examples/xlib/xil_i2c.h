/*
 * =====================================================================================
 *
 *       Filename:  xil_i2c.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 09:02:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_I2C_H_
#define _XIL_I2C_H_
#include "xil_types.h"

typedef struct _xil_i2c xil_i2c;

typedef struct _xil_i2c{
    u8 devaddr;
    int fd;
    int (*Read)(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len);
    int (*Write)(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len);
}xil_i2c;

xil_i2c * XilI2CCreate(char *devname, u8 devaddr);
void XilI2CDestroy(xil_i2c* const me);

#endif
