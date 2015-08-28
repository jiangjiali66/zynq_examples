/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 06:02:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_pwm.h"
#define PWM_BASE_ADDR 0x43C00000

int main()
{
    xil_pwm* mypwm = XilPWMCreate(PWM_BASE_ADDR);
    mypwm->setPeriod(mypwm, 0, 10000);
    mypwm->setDuty(mypwm, 0, 20);
    
    mypwm->setPeriod(mypwm, 1, 10000);
    mypwm->setDuty(mypwm, 1, 40);

    mypwm->setPeriod(mypwm, 2, 10000);
    mypwm->setDuty(mypwm, 2, 60);

    mypwm->setPeriod(mypwm, 3, 10000);
    mypwm->setDuty(mypwm, 3, 80);

    printf("pwm0 Duty is %f\n", mypwm->getDuty(mypwm, 0));
    
    XilPWMDestory(mypwm);
    
    return 0;
}
