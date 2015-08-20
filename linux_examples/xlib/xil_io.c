/*
 * =====================================================================================
 *
 *       Filename:  xil_io.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 03:44:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_io.h"
#include <sys/mman.h>
static u8 X_In8(xil_io *me, u32 RegOffset)
{
    return  *(volatile u8 *)(me->io + RegOffset / sizeof(unsigned long)); 
}

static u16 X_In16(xil_io *me, u32 RegOffset)
{
    return  *(volatile u16 *)(me->io + RegOffset / sizeof(unsigned long));     
}

static u32 X_In32(xil_io *me, u32 RegOffset)
{
    return  *(volatile u32 *)(me->io + RegOffset / sizeof(unsigned long));
}  

static void X_Out8(xil_io *me, u32 RegOffset, u8 Value)
{
    *(volatile u8 *)(me->io + RegOffset / sizeof(unsigned long)) = Value;
}

static void X_Out16(xil_io *me, u32 RegOffset, u16 Value)
{
    *(volatile u16 *)(me->io + RegOffset / sizeof(unsigned long)) = Value;
}

static void X_Out32(xil_io *me, u32 RegOffset, u32 Value)
{
    *(volatile u32 *)(me->io + RegOffset / sizeof(unsigned long)) = Value;
}

static int XilAddrMmap(xil_io *me, u32 Addr)
{
    int fd;
    if((fd = open ("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("mem open error!\n");
        return -1;
    }
    me->io = (unsigned long *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
                                        MAP_SHARED, fd, Addr & ~MAP_MASK);
    if ((unsigned long)me->io == -1)
    {
        printf("mmap failed!\n");
        return -2;
    }

    return 0;
}

static int XilIOInit(xil_io *me, u32 Addr, 
    u8 (*Xil_In8)(xil_io *me, u32 RegOffset),
    u16 (*Xil_In16)(xil_io *me, u32 RegOffset), 
    u32 (*Xil_In32)(xil_io *me, u32 RegOffset), 
    void (*Xil_Out8)(xil_io *me, u32 RegOffset, u8 Value),
    void (*Xil_Out16)(xil_io *me, u32 RegOffset, u16 Value),
    void (*Xil_Out32)(xil_io *me, u32 RegOffset, u32 Value))
{
    memset(me, 0, sizeof(xil_io));
    if(XilAddrMmap(me, Addr) < 0)
    {
        return -1;
    }
    me->Xil_In8 = Xil_In8;
    me->Xil_In16 = Xil_In16;
    me->Xil_In32 = Xil_In32;
    me->Xil_Out8 = Xil_Out8;
    me->Xil_Out16 = Xil_Out16;
    me->Xil_Out32 = Xil_Out32;
}

xil_io *XilIOCreate(u32 Addr)
{
    xil_io *me = (xil_io *)malloc(sizeof(xil_io));
    if(me == NULL)
    {
        printf("xil IO create fail!\n");
        return NULL;
    }
    
    if(XilIOInit(me, Addr, X_In8, X_In16, X_In32, X_Out8, X_Out16, X_Out32) < 0)
    {
        free(me);

        return NULL;
    }

    return me;
}

void XilIODestory(xil_io *me)
{
    if(me == NULL)
    {
        printf("xil IO destory fail!\n");
        return;
    }
    munmap((void *)me->io, BLOCK_SIZE); 
    free(me);

    return;
}
