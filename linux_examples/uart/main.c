/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2015 07:04:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include "xil_uart.h"

#define UART_READ_BYTES_NUM 10
char str[] = "hello world\r\n";
const char uartdev[] = "/dev/ttyPS0";

int main()
{
    char buf[50] = {0};
    xil_uart_config myconfig;
    myconfig.devname    = uartdev;
    myconfig.speed      = 115200;
    myconfig.flow_ctrl  = 0;
    myconfig.databits   = 8;
    myconfig.stopbits   = 1;
    myconfig.parity     = 'N'; 
    xil_uart* myuart = XilUartCreate();

    myuart->open(myuart, myconfig);
    if(!myuart->isopend(myuart))
    {
        printf("uart open failed!\n");
    }   
    myuart->writen(myuart, str, strlen(str));
 
    while(myuart->readline(myuart, buf) == 0);
    printf("myuart readline:%s\n", buf);
    
    memset(buf, 0, strlen(buf));
    while(myuart->readn(myuart, buf, UART_READ_BYTES_NUM) == 0);
    printf("myuart read %d bytes:%s\n", UART_READ_BYTES_NUM, buf);

    myuart->close(myuart);
    
    XilUartDestroy(myuart);

    return 0;
}
