/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/16/2015 01:52:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "xil_dma.h"
#include<sys/time.h>
#define DEVICE_NAME "/dev/xdma"
#define DMA_CH 1

int main()
{
    const int LENGTH = 1024 * 1024;
    int i;
    uint32_t *src;
    uint32_t *dst;
    printf("max image is %d for nom!\n", LENGTH);
    printf("DMA Channel is %d\n", DMA_CH);
    xil_dma *mydma = XilDMACreate(DEVICE_NAME);
    if(mydma == NULL)
    {
        return -1;
    }   
/***************************dma load data**********************************/    
    src = (uint32_t *)mydma->setupAlloc(mydma, LENGTH, sizeof(uint32_t));
    dst = (uint32_t *)mydma->setupAlloc(mydma, LENGTH, sizeof(uint32_t));

    for (i = 0; i < LENGTH; i++) 
    {
        src[i] = 'z';
    }
//    src[LENGTH-1] = '\n';
    for (i = 0; i < LENGTH; i++) 
    {
        dst[i] = 'd';
    }
//    dst[LENGTH-1] = '\n';
    printf("test: dst buffer before transmit:\n");
    for (i = 0; i < 10; i++) 
    {
        printf("%c\t", (char)dst[i]);
    }
    printf("\n");
    
/****************dma Transfer****************************/
    struct  timeval    tv;
    struct  timezone   tz;
    gettimeofday(&tv,&tz);
    long start = tv.tv_sec * 1000000 + tv.tv_usec;
    
    if (0 < mydma->getDevNum(mydma)) 
    {
        mydma->performTransfer(mydma, DMA_CH, 0, src, 
                                        LENGTH, XDMA_MEM_TO_DEV);
        mydma->performTransfer(mydma, DMA_CH, 0, dst, 
                                        LENGTH, XDMA_DEV_TO_MEM);
    }
    while(dst[LENGTH - 2] != src[LENGTH - 2]);
    gettimeofday(&tv,&tz);
    long now = tv.tv_sec * 1000000 + tv.tv_usec - start - 72; 
    int count;
    for (i = 0; i < LENGTH; i++)
    {
        if((char)dst[i] != (char)src[i])
        {
            count = i;
            printf("\n count is %d\n", count);
            break;
        }

        if(i >= LENGTH - 10)
        {
            printf("%c\t", (char)dst[i]);
        }
    }
    printf("\n");
    printf("running time is %ld us\n", now);
   
    XilDMADestory(mydma);

    return 0;
}
