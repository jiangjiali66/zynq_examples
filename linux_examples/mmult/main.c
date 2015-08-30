/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/27/2015 02:26:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_mmult.h"
#include <stdio.h>
#include "xil_dma.h"

#define MMULT_BASE_ADDR 0x43c40000

void matrix_multiply_ref(float a[DIM][DIM], float b[DIM][DIM], float out[DIM][DIM])
{

    int ia, ib, id;
    for (ia = 0; ia < DIM; ++ia)
     for (ib = 0; ib < DIM; ++ib)
     {

         float sum = 0;

         for (id = 0; id < DIM; ++id)

             sum += a[ia][id] * b[id][ib];

         out[ia][ib] = sum;
     }
}

int main()
{
    int i,j;
    float *hw_A;
    float *hw_B;
    float *hw_res;
    float sw_A[DIM][DIM];
    float sw_B[DIM][DIM];
    float sw_res[DIM][DIM];
    xil_mmult *mmult = XilMmultCreate(MMULT_BASE_ADDR, "/dev/xdma", 0);
    hw_A = (float *)mmult->setupAlloc(mmult, DIM * DIM, sizeof(float));
    hw_B = (float *)mmult->setupAlloc(mmult, DIM * DIM, sizeof(float));
    hw_res = (float *)mmult->setupAlloc(mmult, DIM * DIM, sizeof(float));
    memset(hw_A, 0, DIM * DIM * sizeof(float));
    memset(hw_B, 0, DIM * DIM * sizeof(float));
    memset(hw_res, 0, DIM * DIM * sizeof(float));
    for(i = 0; i<DIM; i++)
    {
        for(j = 0; j<DIM; j++)
        {
            sw_A[i][j] = (float)(i+j);
            sw_B[i][j] = (float)(i*j);
        }
    }
 
    memcpy(hw_A, sw_A, DIM * DIM * sizeof(float));
    memcpy(hw_B, sw_B, DIM * DIM * sizeof(float));
    for(i = 0; i<DIM; i++)
    for(j = 0; j<DIM; j++)
    {
       if(hw_A[i*DIM + j] != sw_A[i][j])
        {
            printf("not match!\n");
            break;
        }
    }
    matrix_multiply_ref(sw_A, sw_B, sw_res);
    mmult->step(mmult);
    mmult->run(mmult, hw_A, hw_B, hw_res);
    
    for(i = 0; i<DIM; i++)
    for(j = 0; j<DIM; j++)
    {     
        if(hw_res[i*DIM + j] != sw_res[i][j])
        { 
//             printf("res match!\n");
//             break;
        }
	printf("%.0f ", hw_res[i*DIM + j]); 
    }    
    printf("\n");
    for(i = 0; i<DIM; i++)
    for(j = 0; j<DIM; j++)
    {
	if(hw_res[i*DIM + j] != sw_res[i][j])
        {
             //break;
        }
        printf("%.0f ", sw_res[i][j]);
    }
    printf("\n");
    XilMmultDestroy(mmult);
    return 0;
}
