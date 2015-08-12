/*
 * =====================================================================================
 *
 *       Filename:  xil_types.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/10/2015 03:17:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#ifndef _XIL_TYPES_H_
#define _XIL_TYPES_H_
#include <sys/types.h>

#ifndef TRUE
#  define TRUE      1
#endif

#ifndef FALSE
#  define FALSE     0
#endif

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef enum boolean { true, false } boolean;
#endif
