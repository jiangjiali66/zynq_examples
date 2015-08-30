/*
 * =====================================================================================
 *
 *       Filename:  eeprom.c
 *
 *    Description:  24c02
 *
 *        Version:  1.0
 *        Created:  08/18/2015 10:02:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "xil_types.h"
#include "xil_i2c.h"
#include <stdio.h>
#include <string.h>

#define DEVICE_NAME         "/dev/i2c-1"
#define DEVICE_ADDR         0x50

#define PAGESIZE            16

#define WRITE_BYTE_NUM      74

u8 tx_buf[WRITE_BYTE_NUM] = {0};
u8 rx_buf[WRITE_BYTE_NUM] = {0};

int eepromWrite(xil_i2c* const eeprom, u8 i2c_addr, u8* buf, int len)
{
    int WriteBytes = len;
    int BytesWritten = 0;
    int status;

    u8 addr = i2c_addr;
    while(WriteBytes > 0)
    {
        addr = BytesWritten;
        if(WriteBytes <= PAGESIZE)
        {
            status = eeprom->Write(eeprom, &addr, sizeof(i2c_addr),
                                        buf + BytesWritten, WriteBytes);
            WriteBytes -= WriteBytes;
            BytesWritten += WriteBytes;
        }
        else
        {
            status = eeprom->Write(eeprom, &addr, sizeof(i2c_addr),
                                        buf + BytesWritten, PAGESIZE);
            WriteBytes -= PAGESIZE;
            BytesWritten += PAGESIZE;
        }
        if(!status)
        {
            printf("Test Failed in write\n");
        }
        usleep(10000);
    }
    return status;
}

int eepromRead(xil_i2c* const eeprom, u8 i2c_addr, u8* buf, int len)
{
    int status = eeprom->Read(eeprom, &i2c_addr, sizeof(i2c_addr), buf, len);
    if(status != WRITE_BYTE_NUM)
    {
        printf("Test Failed in read\n");
    }
    return status;
}

int main()
{
    int i;
    u8 i2c_addr = 0x0;
    xil_i2c *eeprom = XilI2CCreate(DEVICE_NAME, DEVICE_ADDR);
    memset(tx_buf, 0x12, WRITE_BYTE_NUM/2);
    memset(tx_buf + WRITE_BYTE_NUM/2, 0x34, WRITE_BYTE_NUM/2);
    int status;
    printf("written data:\n");
    for(i = 0; i < WRITE_BYTE_NUM; i++)
    {
        printf("%.2x ", tx_buf[i]);
    }
    printf("\n");    
    eepromWrite(eeprom, i2c_addr, tx_buf, WRITE_BYTE_NUM);
    
    eepromRead(eeprom, i2c_addr, rx_buf, WRITE_BYTE_NUM);
    
    printf("read data:\n"); 
    for(i = 0; i < WRITE_BYTE_NUM; i++)
    {
        printf("%.2x ", rx_buf[i]);
    }
    printf("\n");
    XilI2CDestroy(eeprom);
    return 0;
}
