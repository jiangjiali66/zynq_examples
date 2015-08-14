/*
 * =====================================================================================
 *
 *       Filename:  xil_wrapper.c
 *
 *    Description:  
 *
 *    Version:  1.0
 *    Created:  07/16/2015 10:13:40 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *     Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *    Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "xil_wrapper.h"
#include <errno.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

ssize_t ReadOneByte(int fd, void *buf)
{
    char *strtmp;
    ssize_t reval;

    if(fd < 0)
    {
        return -1;
    }
    strtmp = (char *)buf;
    reval = read(fd, strtmp, 1);

    return reval;
}

ssize_t Readn(int fd, void *buf, ssize_t count)
{
    char *strtmp;
    ssize_t reval, realcount = 0;

    if(fd < 0)
    {
        return -1;
    }
    strtmp = (char *)buf;
    while (count > 0)
    {
        reval = read(fd, strtmp, count);
        if (reval < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }
        else if (reval > 0)
        {
            count -= reval;
            strtmp += reval;
            realcount += reval;
            continue;
        }
        else
        {
            break;
        }
    }

    return realcount;
}

ssize_t ReadLine(int fd, void *buf)
{
    char *strtmp;
    ssize_t reval, realcount = 0;

    if(fd < 0)
    {
        return -1;
    }
    strtmp = (char *)buf;

    do
    {
        reval = read(fd, strtmp, 1);
        if (reval < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }
        if(*strtmp == '\n' || *strtmp == '\r')
		{
			break;
		}
		realcount++;
		strtmp++;

    }while(1);
	*strtmp = '\0';
    return realcount;
}

ssize_t Writen(int fd, const void *buf, ssize_t count)
{
    char *strtmp;
    ssize_t reval, realcount = count;

    if(fd < 0)
    {
        return -1;
    }
    strtmp = (char *)buf;
    while (count > 0)
    {
        reval = write(fd, strtmp, count);
        if (reval < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                return -1;
            }
        }
        count -= reval;
        strtmp += reval;
    }

    return realcount;
}

ssize_t Sendn(int fd, const void *buf, ssize_t count)
{
    char *strtmp;
    ssize_t reval, realcount = count;

    if(fd < 0)
    {
        return -1;
    }
    if(buf == NULL)
    {
        return 0;
    }

    strtmp = (char *)buf;
    while (count > 0)
    {


        reval = send(fd,strtmp,count>=65532?65531:count, MSG_NOSIGNAL);
        if (reval < 0)
        {
            if (errno == EINTR)
            {


                return -2;
            }
            else
            {

                return -1;
            }
        }
        count -= reval;
        strtmp += reval;
    }

    return realcount;
}

int check_crc16(char trame[], ssize_t len)
{
	ssize_t i, j;
    unsigned short int crc, carry_flag, tmp;
    
    crc = 0xffff;
    for(i = 0; i < len; i ++)
    {
        crc = crc ^ trame[i];
        for(j = 0; j < 8; j ++)
        {
            tmp = crc;
            carry_flag = tmp & 0x0001;
            crc=crc >> 1;
            if(carry_flag == 1)
            {
                crc = crc ^ 0xa001;
            }
        }
    }
    if((trame[len + 1] != (crc >> 8)) || (trame[len] != (crc & 255)))
    {

        printf("crc check failure!\n");

        return 1;
    }

    return 0;    
}

unsigned short int calcul_crc16(char trame[],ssize_t len)
{
    ssize_t i, j;
    unsigned short int crc, carry_flag, tmp;
    
    	crc=0xffff;
    for(i = 0; i < len; i ++)
    {
        crc = crc^trame[i];
        for(j = 0; j < 8; j ++)
        {
            tmp = crc;
            carry_flag = tmp & 0x0001;
            crc = crc >> 1;
            if(carry_flag == 1)
            crc = crc ^ 0xa001;
        }
    }
    trame[len + 1] = crc >> 8;
    trame[len] = crc & 255;
    
	return crc;
}

