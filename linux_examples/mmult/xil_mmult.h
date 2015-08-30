/*
 * =====================================================================================
 *
 *       Filename:  xil_mmult.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2015 10:58:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#ifndef _XIL_MMULT_H_
#define _XIL_MMULT_H_

#include "xil_io.h"
#include "xil_dma.h"
#include "xil_types.h"

#define DIM 16
#define WAIT 1
#define NO_WAIT 0


typedef struct _xil_mmult xil_mmult;

typedef struct _xil_mmult{
    xil_io *io;
    xil_dma *dma;
    int DMAChannel;
    void *(*setupAlloc)(xil_mmult * const me, int length, int size_of_type);
    void  (*resetAlloc)(xil_mmult * const me);
    int (*step)(xil_mmult * const me);
    int (*run)(xil_mmult * const me, float in_a[DIM][DIM], float in_b[DIM][DIM], 
                    float res[DIM][DIM]);
}xil_mmult;

xil_mmult *XilMmultCreate(u32 MmultBaseAddr, char *DMADev, int DMAChannel);
void XilMmultDestroy(xil_mmult *me);

#endif
