/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 10:11:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "../xlib/xil_gpio.h"

#define GPIO_BASE_ADDR  0x41200000

int main()
{
    xil_gpio *my_gpio = XilGpioCreate(GPIO_BASE_ADDR);
    
    my_gpio->modeWrite(my_gpio, GPIO_CH1, 0, XIL_OUTPUT);
    my_gpio->digitalWrite(my_gpio, GPIO_CH1, 0, 1);

    XilGpioDestroy(my_gpio);

    xil_gpio *my_ps_gpio = XilGpioCreate(PS_GPIO_BASEADDR);

    PS_GPIO_BANK my_bank = BANK0;

    my_ps_gpio->modeWrite(my_ps_gpio, my_bank, 0, XIL_OUTPUT);
    my_ps_gpio->digitalWrite(my_ps_gpio, my_bank, 0, 0); 

    XilGpioDestroy(my_ps_gpio);
    return 0;
}
