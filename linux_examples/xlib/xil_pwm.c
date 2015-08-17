/*
 * =====================================================================================
 *
 *       Filename:  xil_pwm.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 04:39:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "xil_pwm.h"
#include <stdlib.h>
#include <string.h>

#define XIL_PWM_REG_SIZE 4
#define XIL_PWM_DUTY_REG_OFFSET(ch) XIL_PWM_REG_SIZE * (ch * 2 + 1)
#define XIL_PWM_PERIOD_REG_OFFSET(ch) XIL_PWM_REG_SIZE * (ch * 2)

static void X_setDuty(xil_pwm *me, u8 ch, float value)
{ 
   me->xIO->Xil_Out32(me->xIO, XIL_PWM_DUTY_REG_OFFSET(ch), 
        me->getPeriod(me, ch) * value / 100 + 0x80000000);
}

static void X_setPeriod(xil_pwm *me, u8 ch, u32 value)
{
    me->xIO->Xil_Out32(me->xIO, XIL_PWM_PERIOD_REG_OFFSET(ch), value);
}

static float X_getDuty(xil_pwm *me, u8 ch)
{
    return (me->xIO->Xil_In32(me->xIO, XIL_PWM_DUTY_REG_OFFSET(ch)) -
                 0x80000000) * 100.0 / 
                 me->xIO->Xil_In32(me->xIO, XIL_PWM_PERIOD_REG_OFFSET(ch));
}

static u32 X_getPeriod(xil_pwm *me, u8 ch)
{
    return me->xIO->Xil_In32(me->xIO, XIL_PWM_PERIOD_REG_OFFSET(ch));
}

static int XilPwmInit(xil_pwm *me, u32 BaseAddress,
    void (*setDuty)(xil_pwm *me, u8 ch, float value),
    void (*setPeriod)(xil_pwm *me, u8 ch, u32 value),
    float (*getDuty)(xil_pwm *me, u8 ch),
    u32 (*getPeriod)(xil_pwm *me, u8 ch))
{
    memset(me, 0, sizeof(xil_pwm));
    me->xIO = XilIOCreate(BaseAddress);
    if(me->xIO == NULL)
    {
        return -1;
    }
    me->setDuty = setDuty;
    me->setPeriod = setPeriod;
    me->getDuty = getDuty;
    me-> getPeriod = getPeriod;

    return 0;
}    

xil_pwm *XilPWMCreate(u32 BaseAddress)
{
    xil_pwm *me = (xil_pwm *)malloc(sizeof(xil_pwm));
    if(me == NULL)
    {
        printf("xil pwm create fail!\n");

        return NULL;
    }
    if(XilPwmInit(me, BaseAddress, X_setDuty, X_setPeriod,
                X_getDuty, X_getPeriod) < 0)
    {
        free(me);
        return NULL;
    }
    
    return me;
}

void XilPWMDestory(xil_pwm *me)
{
    if(me == NULL)
    {
        printf("xil pwm destory fail!\n");

        return;
    }
    XilIODestory(me->xIO);
    free(me);

    return;
}


