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
    u8 mode;
    u8 bits;
    u32 speed;
}xil_spi_config;

typedef struct _xil_spi xil_spi;
typedef struct _xil_spi{
    u8 (*RWOneByte)(xil_spi* const me, u8 buf);
    int (*RWNbyte)(xil_spi* const me, void *txBuf, void *rxBuf, u32 len);
}xil_spi;

xil_spi *me = XilCreateSPI(xil_spi_config config)

#endif
