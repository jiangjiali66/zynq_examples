/*
 * =====================================================================================
 *
 *       Filename:  xil_pwm.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 04:29:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#ifndef _XIL_PWM_H_
#define _XIL_PWM_H_

#include "xil_types.h"
#include "xil_io.h"

typedef struct _xil_pwm xil_pwm;
typedef struct _xil_pwm{
    xil_io *xIO;
    void (*setDuty)(xil_pwm* const me, u8 ch, float value);
    void (*setPeriod)(xil_pwm* const me, u8 ch, u32 value);
    float (*getDuty)(xil_pwm* const me, u8 ch);
    u32 (*getPeriod)(xil_pwm* const me, u8 ch);
}xil_pwm;

xil_pwm *XilPWMCreate(u32 BaseAddress);
void XilPWMDestory(xil_pwm *me);

#endif
