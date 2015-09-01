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
 *         Author:  Jiang JiaJi (@.@), jialij@xilinx.com
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

#ifndef __uint32_t_defined
#define __uint32_t_defined
typedef unsigned long uint32_t;
#endif

#ifndef __uint16_t_defined
#define __uint16_t_defined
typedef unsigned short uint16_t;
#endif

#ifndef __uint8_t_defined
#define __uint8_t_defined
typedef unsigned char uint8_t;
#endif

typedef uint32_t u32;
typedef int32_t s32;

typedef uint16_t u16;
typedef int16_t s16;

typedef uint8_t u8;
typedef int8_t s8;

typedef enum boolean { true, false } boolean;

#endif
