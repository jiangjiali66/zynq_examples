/*
 * =====================================================================================
 *
 *       Filename:  xil_spi.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2015 03:02:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "xil_spi.h"
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static int XilsetSpeed(xil_spi* const me, u32 speed)
{
    me->speed = speed;
    return 0;
}

static u8 XilRWOneByte(xil_spi* const me, u8 buf, u8 cs_change)
{
    int ret;
    u8 rxbuf;
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)&buf,
        .rx_buf = (unsigned long)&rxbuf,
        .len = 1,
        .delay_usecs = me->delay_usecs,
        .speed_hz = me->speed,
        .bits_per_word = me->bits,
        .cs_change = cs_change,
    };
    ret = ioctl(me->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret <= 0)  
    {
        printf("can't send spi message\n");
        return 0;
    }

    return rxbuf;

}

static int XilRWNbyte(xil_spi* const me, u8 *txBuf, u8 *rxBuf, u32 len, u8 cs_change)
{
    int ret;
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)txBuf,
        .rx_buf = (unsigned long)rxBuf,
        .len = len,
        .delay_usecs = me->delay_usecs,
        .speed_hz = me->speed,
        .bits_per_word = me->bits,
        .cs_change = cs_change,
    };
    ret = ioctl(me->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == 1)
    {
        printf("can't send spi message\n");
        return -1;
    }
    return 0;
}

static int XilInit(xil_spi *me, xil_spi_config config, int (*setSpeed)(xil_spi* const me, u32 speed),
                u8 (*RWOneByte)(xil_spi* const me, u8 buf, u8 cs_change),
                int (*RWNbyte)(xil_spi* const me, u8 *txBuf, u8 *rxBuf, u32 len, u8 cs_change))
{
    memset(me, 0, sizeof(xil_spi));
    me->fd = open(config.devname, O_RDWR);
    if(me->fd < 0)
    {
        printf("can't open %s device!\n", config.devname);
        return me->fd;
    }

    int ret = ioctl(me->fd, SPI_IOC_WR_MODE, &config.mode);
    if (ret == -1)
    {
        printf("can't set %s device mode!\n", config.devname);
        goto xil_init_fail;
    }

    ret = ioctl(me->fd, SPI_IOC_WR_BITS_PER_WORD, &config.bits);
    if (ret == -1)
    {
        printf("can't set %s device bits per word!\n", config.devname);
        goto xil_init_fail;
    } 

    ret = ioctl(me->fd, SPI_IOC_WR_MAX_SPEED_HZ, &config.maxspeed);
    if (ret == -1)
    {
        printf("can't set %s device max speed hz!\n", config.devname);
        goto xil_init_fail;
    }

    me->delay_usecs = config.delay_usecs;
    me->bits = config.bits;
    me->speed = config.maxspeed;/*set default speed is maxspeed*/

    me->setSpeed = setSpeed;
    me->RWOneByte = RWOneByte;
    me->RWNbyte = RWNbyte;

    return ret;
xil_init_fail:
    close(me->fd);
    return ret;
}

xil_spi *XilSPICreate(xil_spi_config config)
{
    xil_spi *me = (xil_spi *)malloc(sizeof(xil_spi));
    if(me == NULL)
    {
        printf("Xil SPI Create fail!\n");
        return me;
    }
    if(XilInit(me, config, XilsetSpeed, XilRWOneByte, XilRWNbyte) < 0)
    {
        free(me);
        return NULL;
    }

    return me;
}

void XilSPIDestroy(xil_spi*  me)
{
    if(me == NULL)
    {
        printf("Xil SPI Destroy fail!\n");

        return;
    } 
    close(me->fd);
    free(me);

    return;
}
