/*
 * =====================================================================================
 *
 *       Filename:  xil_dma.c
 *
 *    Description: axi-dma
 *
 *        Version:  1.0
 *        Created:  08/15/2015 01:30:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include <asm/ioctl.h>
#include "xil_dma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define BUS_IN_BYTES 4
#define BUS_BURST 16

#define XDMA_IOCTL_BASE         'W'
#define XDMA_GET_NUM_DEVICES    _IO(XDMA_IOCTL_BASE, 0)
#define XDMA_GET_DEV_INFO       _IO(XDMA_IOCTL_BASE, 1)
#define XDMA_DEVICE_CONTROL     _IO(XDMA_IOCTL_BASE, 2)
#define XDMA_PREP_BUF           _IO(XDMA_IOCTL_BASE, 3)
#define XDMA_START_TRANSFER     _IO(XDMA_IOCTL_BASE, 4)
#define XDMA_STOP_TRANSFER      _IO(XDMA_IOCTL_BASE, 5)
#define XDMA_TEST_TRANSFER      _IO(XDMA_IOCTL_BASE, 6)

static uint32_t xdma_calc_offset(xil_dma* const me, void *ptr)
{
    return (((uint8_t *) ptr) - &me->map[0]);
}

static uint32_t xdma_calc_size(int length, int byte_num)
{
    const int block = (BUS_IN_BYTES * BUS_BURST);
    length = length * byte_num;

    if (0 != (length % block)) {
        length += (block - (length % block));
    }

    return length;
}

static void *setupAlloc(xil_dma* const me, int length, int byte_num)
{
    void *array = &me->map[me->alloc_offset];

    me->alloc_offset += xdma_calc_size(length, byte_num);
    
    return array;
}

static void resetAlloc(xil_dma* const me)
{
    me->alloc_offset = 0;
}

static int Xil_getDevNum(xil_dma* const me)
{
    int num_devices = 0;
    if (ioctl(me->fd, XDMA_GET_NUM_DEVICES, &num_devices) < 0) {
        printf("Error ioctl getting device num\n");
        return -1;
    }
    return num_devices;
}

static int Xil_DMA_Prep_Buf_Ctl(xil_dma* const me, int device_id, uint32_t * ptr, 
                            uint32_t length, enum xdma_direction dir)
{
    struct xdma_buf_info buf;

    buf.chan = (dir==XDMA_MEM_TO_DEV?
               me->xdma_devices[device_id].tx_chan:me->xdma_devices[device_id].rx_chan);
    buf.completion = (dir==XDMA_MEM_TO_DEV?
               me->xdma_devices[device_id].tx_cmp:me->xdma_devices[device_id].rx_cmp);
    buf.cookie = 0;
    buf.buf_offset = (u32) xdma_calc_offset(me, ptr);
    buf.buf_size = (u32) (length * sizeof(ptr[0]));
    buf.dir = dir;
    int ret = (int)ioctl(me->fd, XDMA_PREP_BUF, &buf);
    if(ret < 0) 
    {
        printf("Error ioctl set %s buf\n", dir==XDMA_MEM_TO_DEV?"tx":"rx");
        return ret;
    }

    return 0;
}

static int Xil_DMA_Start_Transfer_Ctl(xil_dma* const me, int device_id, 
                                enum xdma_wait wait, enum xdma_direction dir)
{
    struct xdma_transfer trans;

    trans.chan = (dir==XDMA_MEM_TO_DEV?
            me->xdma_devices[device_id].tx_chan:me->xdma_devices[device_id].rx_chan);
    trans.completion = (dir==XDMA_MEM_TO_DEV?
               me->xdma_devices[device_id].tx_cmp:me->xdma_devices[device_id].rx_cmp);
    trans.cookie = 0;
    trans.wait = (0 != (wait & XDMA_WAIT_SRC));
    int ret = (int)ioctl(me->fd, XDMA_START_TRANSFER, &trans);
    if (ret < 0) 
    {
        printf("Error ioctl start %s trans\n", dir==XDMA_MEM_TO_DEV?"tx":"rx");
        return ret;
    }
    
    return 0;
}

static int Xil_performTransfer(xil_dma* const me, int device_id, enum xdma_wait wait,
                        uint32_t * ptr, uint32_t length, enum xdma_direction dir)
{
    int ret = 0;
    boolean used = ((ptr != NULL) && (length != 0));
    if(!used)
    {
        printf("Error ptr or length is NULL !\n");
        return -1;
    }

    if (device_id >= me->num_of_devices) {
        printf("Error invalid device ID\n");
        return -2;
    }
    
    if(Xil_DMA_Prep_Buf_Ctl(me, device_id, ptr, length, dir))
    {
        printf("Error invalid Prep Buf Ctl\n");
        return -3;
    }
    
    if(Xil_DMA_Start_Transfer_Ctl(me, device_id, wait, dir))
    {
        printf("Error invalid Start Transfer Ctl\n");
        return -4;
    }

    return 0;
}

static int Xil_stopTransfer(xil_dma* const me, int device_id,
                            uint32_t * ptr, uint32_t length,
                            enum xdma_direction dir)
{
    int ret = 0;
    struct xdma_transfer trans;
    boolean used = ((ptr != NULL) && (length != 0));
    if(used)
    {
        return -1;
    }
            
    if (device_id >= me->num_of_devices) {
        printf("Error invalid device ID\n");
        return -1;
    }
    
    trans.chan = (dir==XDMA_MEM_TO_DEV?
            me->xdma_devices[device_id].tx_chan:me->xdma_devices[device_id].rx_chan);
    ret = (int)ioctl(me->fd, XDMA_STOP_TRANSFER, &(trans.chan));
    if (ret < 0) 
    {
        printf("Error ioctl stop %s trans\n", dir==XDMA_MEM_TO_DEV?"src":"dst");
        return ret;
    }
    
    return ret;
}

static int xil_DMAInit(xil_dma* const me, char *dma_device, 
                    int (*getDevNum)(xil_dma* const me),
                    int (*performTransfer)(xil_dma* const me, int device_id,
                        enum xdma_wait wait, uint32_t * ptr, uint32_t length, 
                        enum xdma_direction dir), 
                    int (*stopTransfer)(xil_dma* const me, int device_id,
                        uint32_t * ptr, uint32_t length, enum xdma_direction dir),
                    void *(*setupAlloc)(xil_dma* const me, int length, int byte_num),
                    void (*resetAlloc)(xil_dma* const me))
{
    int i;
    struct xdma_chan_cfg dst_config;
    struct xdma_chan_cfg src_config;

    memset(me, 0, sizeof(xil_dma));
    
    me->fd = open(dma_device, O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0600);
    if(me->fd == -1) 
    {
        printf("Error opening file for writing\n");
        return EXIT_FAILURE;
    }

    me->map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, me->fd, 0);
    if(me->map == MAP_FAILED)
    {
        close(me->fd);
        printf("Error mmapping the file\n");
        return EXIT_FAILURE;
    }    
    me->getDevNum = getDevNum;
    me->performTransfer = performTransfer;
    me->stopTransfer = stopTransfer;
    me->setupAlloc = setupAlloc;
    me->resetAlloc = resetAlloc; 

    me->resetAlloc(me);

    me->num_of_devices = me->getDevNum(me);
    if(me->num_of_devices <= 0) 
    {
        printf("Error no DMA devices found\n");
        return EXIT_FAILURE;
    }
    
    for(i = 0; i < MAX_DEVICES; i++) 
    {
        me->xdma_devices[i].tx_chan = (u32) NULL;
        me->xdma_devices[i].tx_cmp = (u32) NULL;
        me->xdma_devices[i].rx_chan = (u32) NULL;
        me->xdma_devices[i].rx_cmp = (u32) NULL;
        me->xdma_devices[i].device_id = i;

        if(i < me->num_of_devices) 
        {
            if(ioctl(me->fd, XDMA_GET_DEV_INFO, &me->xdma_devices[i]) < 0) 
            {
                printf("Error ioctl getting device info\n");
                return EXIT_FAILURE;
            }

            dst_config.chan = me->xdma_devices[i].rx_chan;
            dst_config.dir = XDMA_DEV_TO_MEM;
            dst_config.coalesc = 1;
            dst_config.delay = 0;
            dst_config.reset = 0;
            if(ioctl(me->fd, XDMA_DEVICE_CONTROL, &dst_config) < 0) 
            {
                printf("Error ioctl config dst (rx) chan\n");
                return EXIT_FAILURE;
            }

            src_config.chan = me->xdma_devices[i].tx_chan;
            src_config.dir = XDMA_MEM_TO_DEV;
            src_config.coalesc = 1;
            src_config.delay = 0;
            src_config.reset = 0;
            if(ioctl(me->fd, XDMA_DEVICE_CONTROL, &src_config) < 0) 
            {
                printf("Error ioctl config src (tx) chan\n");
                return EXIT_FAILURE;
            }
        }
    }

    return 0;
}


xil_dma *XilDMACreate(char *dma_device)
{
    xil_dma *me = (xil_dma *)malloc(sizeof(xil_dma));
    if(me == NULL)
    {
        printf("Error DMA Create Failure!\n");
        return NULL;
    }
    if(xil_DMAInit(me, dma_device, Xil_getDevNum, Xil_performTransfer,
                    Xil_stopTransfer, setupAlloc, resetAlloc) != 0)
    {
        free(me);
        return NULL;
    }
    
    return me;
}
void XilDMADestory(xil_dma *me)
{
    if(me == NULL)
    {
        printf("Error DMA Destory Failure!\n");
        return;
    }
    if(munmap(me->map, FILESIZE) == -1) 
    {
        printf("Error un-mmapping the file\n");
        return;
    }
    close(me->fd);
    free(me); 
}

