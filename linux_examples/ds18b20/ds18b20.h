/*
 * =====================================================================================
 *
 *       Filename:  ds18b20.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2015 03:22:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include "xil_gpio.h"

#define DS18B20_MAX_TMP 125
#define DS18B20_MIN_TMP -55
typedef struct ds18b20{
    float last_tmp;
	xil_gpio *DQ;
	int pin;
    int channel;
    int   (*transform)(struct ds18b20* const me);
	float (*readtemp)(struct ds18b20* const me);
}ds18b20_type;

struct ds18b20 *ds18b20Create(u32 BaseAddr, int channel, int pin);
int ds18b20Destory(struct ds18b20 *me); 
