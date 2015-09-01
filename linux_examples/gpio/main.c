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


#include "xil_gpio.h"

#define GPIO_BASE_ADDR  0x41200000
#define LD0 0
#define LD1 1
#define LD4 7

/**
    当对PS的MIO进行整个bank操作的时候，mode的值与axi gpio相反
    0x0 全输入  0xffff ffff 全输出
 **/

int main()
{

    int i;
    xil_gpio *my_gpio = XilGpioCreate(GPIO_BASE_ADDR);
    
    my_gpio->modeWrite(my_gpio, GPIO_CH1, LD0, XIL_OUTPUT);
    my_gpio->modeWrite(my_gpio, GPIO_CH1, LD1, XIL_OUTPUT);
    for(i = 0; i < 5; i++)
    {
        my_gpio->digitalWrite(my_gpio, GPIO_CH1, LD0, 1);
        my_gpio->digitalWrite(my_gpio, GPIO_CH1, LD1, 1);
        usleep(200000);    
        my_gpio->digitalWrite(my_gpio, GPIO_CH1, LD0, 0);
        my_gpio->digitalWrite(my_gpio, GPIO_CH1, LD1, 0);
        usleep(200000);
    }
    XilGpioDestroy(my_gpio);
/*****以下是对psgpio进行操作，MIO7在zybo被接在了一个led上******/
    xil_gpio *my_ps_gpio = XilGpioCreate(PS_GPIO_BASEADDR);

    my_ps_gpio->modeWrite(my_ps_gpio, 0, LD4, XIL_OUTPUT);
    for(i = 0; i < 5; i++)
    {
        my_ps_gpio->digitalWrite(my_ps_gpio, 0, LD4, 1);
        usleep(200000);
        my_ps_gpio->digitalWrite(my_ps_gpio, 0, LD4, 0);
        usleep(200000);
    }
    XilGpioDestroy(my_ps_gpio);
    return 0;
}
