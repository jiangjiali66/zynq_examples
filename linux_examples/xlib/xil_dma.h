/*
 * =====================================================================================
 *
 *       Filename:  xil_dma.h
 *
 *    Description:  
 *
 *    Version:  1.0
 *    Created:  08/14/2015 05:27:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *     Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *    Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_DMA_H_
#define _XIL_DMA_H_

#include "xil_types.h"

typedef s32 dma_cookie_t;

#define MAP_SIZE  (32*1024*1024)
#define FILESIZE (MAP_SIZE * sizeof(u8))
#define MAX_DEVICES 4
enum xdma_direction {
    XDMA_MEM_TO_DEV,
    XDMA_DEV_TO_MEM,
    XDMA_TRANS_NONE,
};

enum xdma_wait {
    XDMA_WAIT_NONE = 0,
    XDMA_WAIT_SRC = (1 << 0),
    XDMA_WAIT_DST = (1 << 1),
    XDMA_WAIT_BOTH = (1 << 1) | (1 << 0),
};

typedef struct _xdma_dev {
    u32 tx_chan;    /* (struct dma_chan *) */
    u32 tx_cmp; /* (struct completion *) callback_param */
    u32 rx_chan;    /* (struct dma_chan *) */
    u32 rx_cmp; /* (struct completion *) callback_param */
    u32 device_id;
}xdma_dev;

struct xdma_buf_info {
     u32 chan;   /* (struct dma_chan *) */
     u32 completion; /* (struct completion *) callback_param */

     dma_cookie_t cookie;
     u32 buf_offset;
     u32 buf_size;
     enum xdma_direction dir;
};

struct xdma_transfer {
    u32 chan;   /* (struct dma_chan *) */
    u32 completion; /* (struct completion *) callback_param */

    dma_cookie_t cookie;
    u32 wait;   /* true/false */
};

struct xdma_chan_cfg {
    u32 chan;   /* (struct dma_chan *) */

    enum xdma_direction dir;    /* Channel direction */
    int coalesc;    /* Interrupt coalescing threshold */
    int delay;  /* Delay counter */
    int reset;  /* Reset Channel */
};

typedef struct _xil_dma xil_dma;

typedef struct _xil_dma {
    int fd;
    u8 *map;
    u32 alloc_offset;
    int num_of_devices;
    xdma_dev xdma_devices[MAX_DEVICES];
    int (*getDevNum)(xil_dma* const me);
    int (*performTransfer)(xil_dma* const me, int device_id, 
                            enum xdma_wait wait,
                            uint32_t * ptr, uint32_t length,
                            enum xdma_direction dir);
    int (*stopTransfer)(xil_dma* const me, int device_id,  
                            uint32_t * src_ptr, uint32_t src_length,
                            enum xdma_direction dir);
    void *(*setupAlloc)(xil_dma* const me, int length, int byte_num);
    void (*resetAlloc)(xil_dma* const me);
}xil_dma;

xil_dma *XilDMACreate(char *dma_device);
void XilDMADestory(xil_dma *me);

#endif
