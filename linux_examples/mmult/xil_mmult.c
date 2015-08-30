/*
 * =====================================================================================
 *
 *       Filename:  xil_mmult.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2015 12:21:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_mmult.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL 0x0
#define XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_GIE     0x4
#define XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER     0x8
#define XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_ISR     0xc

static void *XilMmultSetupAlloc(xil_mmult * const me, int length, int size_of_type)
{
    return me->dma->setupAlloc(me->dma, length, size_of_type);
}

static void XilMmultResetAlloc(xil_mmult * const me)
{
    me->dma->resetAlloc(me->dma);
}

static void XMmult_accel_core_Start(xil_mmult * const me)
{
    u32 Data = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL) & 0x80;
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL, Data | 0x01);
}

static u32 XMmult_accel_core_IsDone(xil_mmult * const me)
{
    u32 Data = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

static u32 XMmult_accel_core_IsIdle(xil_mmult * const me)
{
    u32 Data = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

static u32 XMmult_accel_core_IsReady(xil_mmult * const me)
{
    u32 Data = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL);
    return (Data >> 0) & 0x1;
}

static void XMmult_accel_core_EnableAutoRestart(xil_mmult * const me)
{
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL, 0x80);
}

static void XMmult_accel_core_DisableAutoRestart(xil_mmult * const me)
{
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_AP_CTRL, 0x0);
}

static void XMmult_accel_core_InterruptGlobalEnable(xil_mmult * const me)
{
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_GIE, 1);
}

static void XMmult_accel_core_InterruptGlobalDisable(xil_mmult * const me)
{
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_GIE, 0);
}

static void XMmult_accel_core_InterruptEnable(xil_mmult * const me,  u32 Mask) 
{
    u32 Register = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER);
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER, Register | Mask);
}

static void XMmult_accel_core_InterruptDisable(xil_mmult * const me,  u32 Mask) 
{
    u32 Register = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER);
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER, Register & (~Mask));
}

static void XMmult_accel_core_InterruptClear(xil_mmult * const me, u32 Mask)
{
    u32 Register = me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_ISR);
    me->io->Xil_Out32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER, Register & Mask);
}

static u32 XMmult_accel_core_InterruptGetEnabled(xil_mmult * const me)
{
    return me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_IER);
}

static u32 XMmult_accel_core_InterruptGetStatu(xil_mmult * const me)
{
    return me->io->Xil_In32(me->io, XMMULT_ACCEL_CORE_CONTROL_BUS_ADDR_ISR);
}

static int XilMmultStep(xil_mmult * const me)
{
    XMmult_accel_core_InterruptGlobalDisable(me);
    //XMmult_accel_core_InterruptEnable(me, 1);
    //XMmult_accel_core_InterruptGlobalEnable(me);
    XMmult_accel_core_Start(me);
    if(!XMmult_accel_core_IsReady(me))
    {
       printf("Mmult accel core start fail!\n");
    }
    return 0;
}

static int XilMmultRun(xil_mmult * const me, float in_a[DIM][DIM], float in_b[DIM][DIM],
                                    float res[DIM][DIM])
{
    if (0 < me->dma->getDevNum(me->dma)) 
    {
        if(me->dma->performTransfer(me->dma, me->DMAChannel, WAIT, 
				(uint32_t *)in_a, DIM * DIM, 
				XDMA_MEM_TO_DEV) != 0)
        {
            return -1;
        }
    }
    if (0 < me->dma->getDevNum(me->dma))
    {
        if(me->dma->performTransfer(me->dma, me->DMAChannel, WAIT, 
				(uint32_t *)in_b, DIM * DIM, 
				XDMA_MEM_TO_DEV) != 0)
        {
            return -2;
        }
    }
    if (0 < me->dma->getDevNum(me->dma))
    {
        if(me->dma->performTransfer(me->dma, me->DMAChannel, WAIT, 
				(uint32_t *)res, DIM * DIM, 
				XDMA_DEV_TO_MEM) != 0)
        {
            return -3;
        }
    }
    return 0;
}

static int XilMmultInit(xil_mmult * const me, u32 MmultBaseAddr, char *DMADev, int DMAChannel,
                    void *(*setupAlloc)(xil_mmult * const me, int length, int size_of_type),
                    void  (*resetAlloc)(xil_mmult * const me),
                    int (*step)(xil_mmult * const me),
                    int (*run)(xil_mmult * const me, float in_a[DIM][DIM], float in_b[DIM][DIM], 
                                    float res[DIM][DIM]))
{
    memset(me, 0, sizeof(xil_mmult));
    me->dma = XilDMACreate(DMADev);
    if(me->dma == NULL)
    {
        return -1;
    }

    me->io = XilIOCreate(MmultBaseAddr);
    if(me->dma == NULL)
    {
        return -2;
    }
    me->DMAChannel = DMAChannel;
    me->setupAlloc = setupAlloc;
    me->resetAlloc = resetAlloc;
    me->step = step;
    me->run = run;

    return 0;
}

xil_mmult *XilMmultCreate(u32 MmultBaseAddr, char *DMADev, int DMAChannel)
{
    
    xil_mmult *me = malloc(sizeof(xil_mmult));
    if(me == NULL)
    {
        printf("Xil Mmult Create fail!\n");
        return me;
    }
    if(XilMmultInit(me, MmultBaseAddr, DMADev, DMAChannel,
                    XilMmultSetupAlloc, XilMmultResetAlloc,
                    XilMmultStep, XilMmultRun) < 0)
    {
        free(me);
        return NULL;
    }

    return me;
}

void XilMmultDestroy(xil_mmult *me)
{
    if(me == NULL)
    {
        printf("xil Mmult Destroy fail!\n");
        return;
    }
    free(me);

    return;
}
