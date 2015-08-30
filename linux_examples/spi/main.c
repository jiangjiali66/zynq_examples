/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 03:44:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_spi.h"
#include <stdio.h>

#define DEVNAME "/dev/spidev32766.0"

int main()
{
    int i;
    xil_spi_config config = {
        .devname = DEVNAME,
        .mode = SPI_MODE_0,
        .bits = 8,
        .maxspeed = 5000,
    };
    xil_spi *myspi = XilSPICreate(config);
    uint8_t tx[] = {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
                0xF0, 0x0D,
    };
    uint8_t rx[sizeof(tx)] = {0};

    printf("spi test tx buf:\n");
    for(i=0;i<sizeof(tx);i++)
    {
        printf("%.2x ", tx[i]);
    }
    printf("\n");
    printf("RWNbyte test rx buf:\n");
    myspi->RWNbyte(myspi, tx, rx, sizeof(tx), 0);
    for(i=0;i<sizeof(tx);i++)
    {
        printf("%.2x ", rx[i]);
    }
    printf("\n");
    printf("RWOneByte test rx buf:\n");
    for(i=0;i<sizeof(tx);i++)
    {
        printf("%.2x ", myspi->RWOneByte(myspi, tx[i], 0));
    }
    printf("\n");

    XilSPIDestroy(myspi);
    
    return 0;
}
