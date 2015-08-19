/*
 * =====================================================================================
 *
 *       Filename:  xil_gpio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 06:58:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_gpio.h"
#include <stdlib.h>
#include <string.h>

#define XGPIO_CHAN_OFFSET  8

#define XGPIO_IR_MASK       0x3 /**< Mask of all bits */
#define XGPIO_IR_CH1_MASK   0x1 /**< Mask for the 1st channel */
#define XGPIO_IR_CH2_MASK   0x2 /**< Mask for the 2nd channel */

#define XGPIO_GIE_GINTR_ENABLE_MASK 0x80000000

#define XGPIO_DATA_OFFSET   0x0   /**< Data register for 1st channel */
#define XGPIO_TRI_OFFSET    0x4   /**< I/O direction reg for 1st channel */
#define XGPIO_DATA2_OFFSET  0x8   /**< Data register for 2nd channel */
#define XGPIO_TRI2_OFFSET   0xC   /**< I/O direction reg for 2nd channel */

#define XGPIO_GIE_OFFSET    0x11C /**< Glogal interrupt enable register */
#define XGPIO_ISR_OFFSET    0x120 /**< Interrupt status register */
#define XGPIO_IER_OFFSET    0x128 /**< Interrupt enable register */


#define XGPIOPS_DATA_LSW_OFFSET  0x000  /* Mask and Data Register LSW, WO */
#define XGPIOPS_DATA_MSW_OFFSET  0x004  /* Mask and Data Register MSW, WO */
#define XGPIOPS_DATA_OFFSET  0x040  /* Data Register, RW */
#define XGPIOPS_DATA_RO_OFFSET   0x060  /* Data Register - Input, RO */
#define XGPIOPS_DIRM_OFFSET  0x204  /* Direction Mode Register, RW */
#define XGPIOPS_OUTEN_OFFSET     0x208  /* Output Enable Register, RW */
#define XGPIOPS_INTMASK_OFFSET   0x20C  /* Interrupt Mask Register, RO */
#define XGPIOPS_INTEN_OFFSET     0x210  /* Interrupt Enable Register, WO */
#define XGPIOPS_INTDIS_OFFSET    0x214  /* Interrupt Disable Register, WO*/
#define XGPIOPS_INTSTS_OFFSET    0x218  /* Interrupt Status Register, RO */
#define XGPIOPS_INTTYPE_OFFSET   0x21C  /* Interrupt Type Register, RW */
#define XGPIOPS_INTPOL_OFFSET    0x220  /* Interrupt Polarity Register, RW */
#define XGPIOPS_INTANY_OFFSET    0x224  /* Interrupt On Any Register, RW */
/* @} */

/** @name Register offsets for each Bank.
 *  *  @{
 *   */
#define XGPIOPS_DATA_MASK_OFFSET 0x8  /* Data/Mask Registers offset */
#define XGPIOPS_DATA_BANK_OFFSET 0x4  /* Data Registers offset */
#define XGPIOPS_REG_MASK_OFFSET 0x40  /* Registers offset */

/* For backwards compatibility */
#define XGPIOPS_BYPM_MASK_OFFSET    XGPIOPS_REG_MASK_OFFSET

/** @name Interrupt type reset values for each bank
 *  *  @{
 *   */
#define XGPIOPS_INTTYPE_BANK0_RESET  0xFFFFFFFF
#define XGPIOPS_INTTYPE_BANK1_RESET  0x3FFFFFFF
#define XGPIOPS_INTTYPE_BANK2_RESET  0xFFFFFFFF
#define XGPIOPS_INTTYPE_BANK3_RESET  0xFFFFFFFF


void ps_modeChipWrite(xil_gpio * const me, u8 ch, u32 value)
{
    if(ch < 0 || ch > 4)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n", 
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    } 
    me->xIO->Xil_Out32(me->xIO, (ch * XGPIOPS_REG_MASK_OFFSET) + 
                            XGPIOPS_DIRM_OFFSET, ~value);
    me->xIO->Xil_Out32(me->xIO, (ch * XGPIOPS_REG_MASK_OFFSET) +
                            XGPIOPS_OUTEN_OFFSET, ~value);
}

u32 ps_modeChipRead(xil_gpio * const me, u8 ch)
{
    if(ch < 0 || ch > 4)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    return ~me->xIO->Xil_In32(me->xIO, (ch * XGPIOPS_REG_MASK_OFFSET) +
                XGPIOPS_DIRM_OFFSET);
    
}

void ps_digitalChipWrite(xil_gpio * const me, u8 ch, u32 value)
{
    if(ch < 0 || ch > 4)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    me->xIO->Xil_Out32(me->xIO, (ch * XGPIOPS_DATA_BANK_OFFSET) +
              XGPIOPS_DATA_OFFSET, value);
}

u32 ps_digitalChipRead(xil_gpio * const me, u8 ch)
{
    if(ch < 0 || ch > 4)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    return me->xIO->Xil_In32(me->xIO, (ch * XGPIOPS_REG_MASK_OFFSET) +
                XGPIOPS_DATA_OFFSET);

}

void X_digitalChipWrite(xil_gpio * const me, u8 ch, u32 value)
{
    if(ch < 1 || ch > 2)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n", 
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    me->xIO->Xil_Out32(me->xIO, ((ch - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET,
                            value);
}

u32 X_digitalChipRead(xil_gpio * const me, u8 ch)
{
    if(ch < 1 || ch > 2)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n", 
                    __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    return me->xIO->Xil_In32(me->xIO, ((ch - 1) * XGPIO_CHAN_OFFSET) + 
                                XGPIO_DATA_OFFSET);
}

void X_modeChipWrite(xil_gpio * const me, u8 ch, u32 value)
{
    if(ch < 1 || ch > 2)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n", 
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    me->xIO->Xil_Out32(me->xIO, ((ch - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET,
                            value);
}

u32 X_modeChipRead(xil_gpio * const me, u8 ch)
{
    if(ch < 1 || ch > 2)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n", 
                    __FILE__, __FUNCTION__, __LINE__);
        return 0;
    }
    return me->xIO->Xil_In32(me->xIO, ((ch - 1) * XGPIO_CHAN_OFFSET) + 
                                XGPIO_TRI_OFFSET);
}

void X_digitalWrite(xil_gpio * const me, u8 ch, u8 pin, boolean value)
{
    if(pin < 0 || pin > 31)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    u32 data = me->digitalChipRead(me, ch);
    if(value)
    {
        data = data | (1 << pin);
    }
    else
    {
        data = data & (0xffffffff - 1 << pin);
    }
    
    me->digitalChipWrite(me, ch, data);
}

boolean X_digitalRead(xil_gpio * const me, u8 ch, u8 pin)
{
    if(pin < 0 || pin > 31)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    return (me->digitalChipRead(me, ch) & (1 << pin))?1:0;
}

void X_modeWrite(xil_gpio * const me, u8 ch, u8 pin, boolean value)
{
    if(pin < 0 || pin > 31)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    u32 data = me->modeChipRead(me, ch);
    if(value)
    {
        data = data | (1 << pin);
    }
    else
    {
        data = data & (0xffffffff - 1 << pin);
    }
    me->modeChipWrite(me, ch, data);
}

boolean X_modeRead(xil_gpio * const me, u8 ch, u8 pin)
{
    if(pin < 0 || pin > 31)
    {
        printf("[file:%s__function:%s__linefile:%d]out of memory!\n",
                    __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    return (me->modeChipRead(me, ch) & (1 << pin))?1:0;
}

int XilGpioInit(xil_gpio* const me, u32 BaseAddress,
                void (*digitalWrite)(xil_gpio * const me, u8 ch, u8 pin, boolean value),
                void (*modeWrite)(xil_gpio * const me, u8 ch, u8 pin, boolean value),
                boolean (*digitalRead)(xil_gpio * const me, u8 ch, u8 pin),
                boolean (*modeRead)(xil_gpio * const me, u8 ch, u8 pin),
                void (*digitalChipWrite)(xil_gpio * const me, u8 ch, u32 value),
                void (*modeChipWrite)(xil_gpio * const me, u8 ch, u32 value),
                u32 (*digitalChipRead)(xil_gpio * const me, u8 ch),
                u32 (*modeChipRead)(xil_gpio * const me, u8 ch))
{
    memset(me, 0, sizeof(xil_gpio));
    me->xIO = XilIOCreate(BaseAddress);
    if(me->xIO == NULL)
    {
        return -1;
    }
    me->digitalWrite = digitalWrite;
    me->modeWrite = modeWrite;
    me->digitalRead = digitalRead;
    me->modeRead = modeRead;
    me->digitalChipWrite = digitalChipWrite;
    me->modeChipWrite = modeChipWrite;
    me->digitalChipRead = digitalChipRead;
    me->modeChipRead = modeChipRead;

    return 0;
}

xil_gpio *XilGpioCreate(u32 BaseAddress)
{
    xil_gpio *me = (xil_gpio *)malloc(sizeof(xil_gpio));
    if(me == NULL)
    {
        printf("xil gpio create fail!\n");
        return NULL;
    }
    if(XilGpioInit(me, BaseAddress, X_digitalWrite, X_modeWrite,
                    X_digitalRead, X_modeRead, 
                    BaseAddress!=PS_GPIO_BASEADDR?X_digitalChipWrite:ps_digitalChipWrite, 
                    BaseAddress!=PS_GPIO_BASEADDR?X_modeChipWrite:ps_modeChipWrite, 
                    BaseAddress!=PS_GPIO_BASEADDR?X_digitalChipRead:ps_digitalChipRead, 
                    BaseAddress!=PS_GPIO_BASEADDR?X_modeChipRead:ps_modeChipRead) < 0)
    {
        free(me);
        return NULL;
    }

    return me;
    
}

void XilGpioDestroy(xil_gpio *me)
{
    if(me == NULL)
    {
        printf("xil gpio destory fail!\n");

        return;
    }
    XilIODestory(me->xIO);
    free(me);

    return;
}
