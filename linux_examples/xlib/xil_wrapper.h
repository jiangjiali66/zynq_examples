/*
 * =====================================================================================
 *
 *       Filename:  xil_wrapper.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/16/2015 10:28:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#ifndef _XIL_WRAPPER_H_
#define _XIL_WRAPPER_H_
#include <sys/types.h>
ssize_t ReadOneByte(int fd, void *buf);

ssize_t Readn(int fd, void *buf, ssize_t count);

ssize_t ReadLine(int fd, void *buf);

ssize_t Writen(int fd, const void *buf, ssize_t count);

ssize_t Sendn(int fd, const void *buf, ssize_t count);

int check_crc16(char trame[], ssize_t len);

unsigned short int calcul_crc16(char trame[],ssize_t len);


#endif
