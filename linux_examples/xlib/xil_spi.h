/*
 * =====================================================================================
 *
 *       Filename:  xil_spi.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 02:07:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_SPI_H_
#define _XIL_SPI_H_

#include <linux/spi/spidev.h>  
#include "xil_types.h"

typedef struct _xil_spi_config{
    char *devname;
    u8 mode;
    u8 bits;
    u32 maxspeed;
    u16 delay_usecs;
}xil_spi_config;

typedef struct _xil_spi xil_spi;
typedef struct _xil_spi{
    u8 bits;
    u16 delay_usecs;
    u32 speed;
    int fd;
    int (*setSpeed)(xil_spi* const me, u32 speed);
    u8 (*RWOneByte)(xil_spi* const me, u8 buf, u8 cs_change);
    int (*RWNbyte)(xil_spi* const me, u8 *txBuf, u8 *rxBuf, u32 len, u8 cs_change);
}xil_spi;

xil_spi *XilSPICreate(xil_spi_config config);
void XilSPIDestroy(xil_spi*  me); 

#endif
