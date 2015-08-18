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
    xil_gpio *mygpio = XilGpioCreate(GPIO_BASE_ADDR);
    
    mygpio->modeWrite(mygpio, GPIO_CH1, 0, XIL_OUTPUT);
    mygpio->digitalWrite(mygpio, GPIO_CH1, 0, 1);

    mygpio->modeWrite(mygpio, GPIO_CH2, 0, XIL_INPUT);
    printf("gpio is %s\n", mygpio->digitalRead(mygpio, GPIO_CH2, 0)? "ON":"OFF"); 
    
    return 0;
}
