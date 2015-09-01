/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/16/2015 06:59:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include "ds18b20.h"

#define DQ_BASE_ADDR    0x41210000
#define DQ_PIN          0
#define DQ_CHANNEL      GPIO_CH1

int main()
{
	struct ds18b20* mysensor = ds18b20Create(DQ_BASE_ADDR, DQ_CHANNEL, DQ_PIN);
	if(mysensor == NULL)
	{
		return -1;
	}
	while(1)
	{
		usleep(1000);
		if(mysensor->transform(mysensor) != 0)
		{
			continue;
		}
		sleep(1);
		printf("temp is %.2f\n", mysensor->readtemp(mysensor));
	}
	ds18b20Destory(mysensor);
	return 0;
}
