/*
 * =====================================================================================
 *
 *       Filename:  xil_uart.c
 *
 *    Description:  
 *
 *    Version:  1.0
 *    Created:  07/16/2015 11:18:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *     Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *    Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "xil_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static int uart_set(int fd, xil_uart_config config)
{
    int i;
    struct termios options;
    int  const speed_arr[] = {
                B115200, B19200, B9600, B4800, B2400, B1200, B300 };
    long const name_arr[] = {
                115200,  19200,  9600,  4800,  2400,  1200,  300 };

    if(tcgetattr(fd,&options) != 0)
    {
        perror("setup serial error!");
        return -1;
    }

    for(i = 0;i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if(config.speed == name_arr[i])
        {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
            break;
        }
    }

    options.c_cflag |= CLOCAL;

    options.c_cflag |= CREAD;

    switch(config.flow_ctrl)
    {
        case 0 :
            options.c_cflag &= ~CRTSCTS;
            break;

        case 1 :
            options.c_cflag |= ~CRTSCTS;
            break;

        case 2 :
            options.c_cflag |= IXON | IXOFF | IXANY;
            break;

        default:
            perror("Unsupported flow_ctrl!");
            return -1;
    }

    options.c_cflag &= ~CSIZE;
    switch(config.databits)
    {
        case 5 :
            options.c_cflag |= CS5;
            break;
        case 6 :
            options.c_cflag |= CS6;
            break;
        case 7 :
            options.c_cflag |= CS7;
            break;
        case 8 :
            options.c_cflag |= CS8;
            break;
        default :
            perror("Unsupported data size!");
            return -1;
    }

    switch(config.parity)
    {
        case 'n' :
        case 'N' :
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        case 'o' :
        case 'O' :
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK;
            break;
        case 'e' :
        case 'E' :
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;
            break;
        case 's' :
        case 'S' :
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
        default :
            perror("Unsupported parity!");
            return -1;

    }

    switch(config.stopbits)
    {
        case 1 :
            options.c_cflag &= ~CSTOPB;
            break;
        case 2 :
            options.c_cflag |= CSTOPB;
            break;
        default:
            perror("Unsupported stop bits!");
            return -1;
    }

    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] =  0;
    options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    tcflush(fd, TCIFLUSH);

    if(tcsetattr(fd, TCSANOW, &options) != 0)
    {
        perror("uart set error!");
        return -1;
    }

    return 0;
}

static int xuart_open(xil_uart* const me, xil_uart_config xconfig)
{
	int err = 0;
	memcpy(&me->config, &xconfig, sizeof(xil_uart_config));
    me->fd = open(me->config.devname, O_RDWR | O_NOCTTY | O_NDELAY);
    if(me->fd < 0)
    {
        perror("Can`t Open Serial Port");
        return -1;
    }

    if((err = fcntl(me->fd, F_SETFL, 0)) < 0)
    {
        perror("fcntl failed!");
        return -1;
    }
    else
    {
        printf("fcntl = %d\n", err);
    }
    if(0 == isatty(STDIN_FILENO))
    {
        perror("standard input is not a terminal device");
        return -1;
    }
    else
    {
        printf("isatty success!\n");
    }
    printf("uart->fd = %d\n", me->fd);
    
    return uart_set(me->fd, me->config);
}

static int xuart_close(xil_uart * const me)
{
	
    int status =  close(me->fd);
	me->fd = 0;

	return status;

}

static int xuart_readn(xil_uart* const me, void *buf, ssize_t count)
{
	struct timeval timeout;
    fd_set fs_read;
	timeout.tv_sec = 0;
    timeout.tv_usec = 5000;

    FD_ZERO(&fs_read);
    FD_SET(me->fd, &fs_read);
	int err = select(me->fd + 1, &fs_read, NULL, NULL, &timeout);
	if(err > 0)
    {
		return Readn(me->fd, buf, count);
	}
	return err;
}

static int xuart_readline(xil_uart* const me, void *buf)
{
	struct timeval timeout;
    fd_set fs_read;
    timeout.tv_sec = 0;
    timeout.tv_usec = 5000;

    FD_ZERO(&fs_read);
    FD_SET(me->fd, &fs_read);
    int err = select(me->fd + 1, &fs_read, NULL, NULL, &timeout);
    if(err > 0)
    {
		return ReadLine(me->fd, buf);
	}

	return err;
}

static int xuart_writen(xil_uart* const me, const void *buf, ssize_t count)
{
	
	return Writen(me->fd, buf, count);
}

static int xuart_isopend(xil_uart * const me)
{
	return me->fd > 0;
}

static void xuartInit(xil_uart* const me, 
			int (*open)(xil_uart* const me, xil_uart_config xconfig), 
			int (*close)(xil_uart* const me), 
			int (*readn)(xil_uart* const me, void *buf, ssize_t count),	
			int (*readline)(xil_uart* const me, void *buf), 
			int (*writen)(xil_uart* const me, const void *buf, ssize_t count),
			int (*isopend)(xil_uart * const me))
{
	memset(me, 0, sizeof(xil_uart));
	me->open = open;
	me->close = close;
	me->readn = readn;
	me->readline = readline;
	me->writen = writen;
	me->isopend = isopend;
	
	return;	
}

xil_uart *XilUartCreate(void)
{
	xil_uart *me = (xil_uart *)malloc(sizeof(xil_uart));
	if(me != NULL)
	{
		xuartInit(me, xuart_open, xuart_close, xuart_readn, xuart_readline, xuart_writen, xuart_isopend);
	}

	return me;
}

void XilUartDestroy(xil_uart * const me)
{
	if(me != NULL)
    {
        free(me);
    }
	
	return;
}
