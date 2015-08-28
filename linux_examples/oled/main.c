/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/19/2015 11:22:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_oled.h"

int main()
{
    LED_Init();
    LED_P6x8Str(1, 1, "hello world!");
    LED_Uninit();
    return 0;
}
