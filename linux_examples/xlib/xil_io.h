/*
 * =====================================================================================
 *
 *       Filename:  xil_io.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 03:17:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_IO_H_
#define _XIL_IO_H_
#include "xil_types.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <errno.h>

#define BLOCK_SIZE (4 * 1024)
#define MAP_MASK (BLOCK_SIZE - 1)

typedef struct _xil_io xil_io;

typedef struct _xil_io{
    volatile unsigned long *io;
    u8 (*Xil_In8)(xil_io *me, u32 RegOffset);
    u16 (*Xil_In16)(xil_io *me, u32 RegOffset);
    u32 (*Xil_In32)(xil_io *me, u32 RegOffset);

    void (*Xil_Out8)(xil_io *me, u32 RegOffset, u8 Value);
    void (*Xil_Out16)(xil_io *me, u32 RegOffset, u16 Value);
    void (*Xil_Out32)(xil_io *me, u32 RegOffset, u32 Value);
}xil_io;

xil_io *XilIOCreate(u32 Addr);
void XilIODestory(xil_io *me);

#endif
