/*
 * =====================================================================================
 *
 *       Filename:  xil_uart.h
 *
 *    Description:  
 *
 *    Version:  1.0
 *    Created:  07/16/2015 10:41:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *     Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *    Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_UART_H_
#define _XIL_UART_H_
#include "xil_types.h"
#include "xil_wrapper.h"

typedef struct _xil_uart_config{
    const char *devname;
    long speed;
    int flow_ctrl;
    int databits;
    int stopbits;
    char parity;
}xil_uart_config;

typedef struct _xil_uart xil_uart;

typedef struct _xil_uart{	
    int fd;
	xil_uart_config config;
	int (*open)(xil_uart* const me, xil_uart_config xconfig);
    int (*close)(xil_uart* const me);
    int (*readn)(xil_uart* const me, void *buf, ssize_t count);
    int (*readline)(xil_uart* const me, void *buf);
    int (*writen)(xil_uart* const me, const void *buf, ssize_t count);
	int (*isopend)(xil_uart * const me);
}xil_uart;

xil_uart *XilUartCreate(void);
void XilUartDestroy(xil_uart * const me);

#endif
