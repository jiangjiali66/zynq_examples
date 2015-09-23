/*
 * =====================================================================================
 *
 *       Filename:  xil_i2c.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 09:14:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "xil_i2c.h"
#include "xil_wrapper.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>

#define I2C_SLAVE_FORCE     0x0706
#define I2C_SLAVE           0x0703    /* Change slave address            */
#define I2C_FUNCS           0x0705    /* Get the adapter functionality */
#define I2C_RDWR            0x0707    /* Combined R/W transfer (one stop only)*/
#define SHORT_FRAME_LEN     0xff

int Xil_I2C_read(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len)
{
    int Status = ioctl(me->fd, I2C_SLAVE_FORCE, me->devaddr);
    if(Status < 0)
    {
        printf("Unable to set the device address\n");

        return -1;
    }
    u8 TransferBuf[addrsize];
    int index;
  
    for(index = 1; index <= addrsize; index ++)
    {
        TransferBuf[index] = ((u8 *)addr)[addrsize - index];
    }
    write(me->fd, (u8 *)TransferBuf, addrsize);
    return read(me->fd, buf, len);
}

int Xil_I2C_write(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len)
{
    u8 *TransferBuf;
    u8 tmp[SHORT_FRAME_LEN + addrsize];
    int Status = ioctl(me->fd, I2C_SLAVE_FORCE, me->devaddr);
    if(Status < 0)
    {
        printf("Unable to set the device address\n");
        
        return -1;
    }
    
    if(len <= SHORT_FRAME_LEN)
    {
        TransferBuf = tmp;
    }
    else
    {
        TransferBuf = (u8 *)malloc(len + addrsize);
    }
    int index;
    
    for(index = 1; index <= addrsize; index ++)
    {
	TransferBuf[index] = ((u8 *)addr)[addrsize - index];
    }

    memcpy(TransferBuf + addrsize, buf, len);

    return write(me->fd, TransferBuf, len + addrsize);
}

static int XilI2cInit(xil_i2c* const me, char *devname, u8 devaddr,
                           int (*Read)(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len),
                           int (*Write)(xil_i2c* const me, void *addr, int addrsize, u8 *buf, int len))
{
    memset(me, 0, sizeof(xil_i2c));
    me->devaddr = devaddr;
    me->fd = open(devname, O_RDWR);
    if(me->fd < 0)
    {
        printf("Cannot open the %s device\n", devname);
        return -1;
    }
    
    me->Read = Read;
    me->Write = Write;

    return 0;
}

xil_i2c * XilI2CCreate(char *devname, u8 devaddr)
{
    xil_i2c *me = (xil_i2c *)malloc(sizeof(xil_i2c));
    if(me == NULL)
    {
        printf("xil i2c create fail!\n");
        return me;
    }
    if(XilI2cInit(me, devname, devaddr, Xil_I2C_read, Xil_I2C_write) < 0)
    {
        free(me);
        return NULL;
    }

    return me;
}

void XilI2CDestroy(xil_i2c *me)
{
    if(me == NULL)
    {
        printf("xil i2c destroy fail!\n");
        return;
    }
    close(me->fd);
    free(me);

    return;
}
