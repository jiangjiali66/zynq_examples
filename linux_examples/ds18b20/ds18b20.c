/*
 * =====================================================================================
 *
 *       Filename:  ds18b20.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2015 08:35:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), jiangjiali666@gmail.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */
#include <sys/time.h>
#include <sys/mman.h>
#include "ds18b20.h"

static int xUsDelay(int us)
{
	struct timeval start, now;
	gettimeofday(&start, NULL);
	int delaytime =  start.tv_usec + us * 0.8;
	do
	{
		gettimeofday(&now, NULL);
	}
	while(now.tv_usec + (now.tv_sec - start.tv_sec) * 1000  < delaytime);
	return 0;
}

static int ds18b20Reset(struct ds18b20* const me)
{
	int i;
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x0);
	xUsDelay(480);
	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_INPUT);
	xUsDelay(40);
	for(i = 0;i < 10;i ++)
	{
		if(!me->DQ->digitalRead(me->DQ, me->channel, me->pin))
		{
			xUsDelay(240);
        	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
            me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);
			return 0;
		}
		xUsDelay(10);
	}
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
	return -1;
}

static unsigned char ds18b20ReadOneByte(struct ds18b20* const me)
{
	int i;
	unsigned char dat = 0;
	
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
	for(i = 8; i > 0; i--)
	{
		me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x0);
		dat >>= 1;
		xUsDelay(3);
		me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);
		xUsDelay(5);
		me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_INPUT);
		if(me->DQ->digitalRead(me->DQ, me->channel, me->pin))
		{
			dat |= 0x80;
		}
		else
		{
			dat &= ~(0x80);
		}
		xUsDelay(3);
		me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
		me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);
		xUsDelay(30);
	}
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);
	return dat;
}

static int ds18b20WriteOneByte(struct ds18b20* const me, unsigned char dat)
{
	int i;
	me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
	for(i = 8; i > 0; i--)
	{
	    	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x0);
        	xUsDelay(1);
        	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, dat & 0x01);
		xUsDelay(40);
	    	me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 0x1);	
		dat >>= 1;
	}

	return 0;
}

static int ds18b20_transform(struct ds18b20* const me)
{
	if(ds18b20Reset(me) != 0)
	{
		printf("not found sensor feedback!\n");
		return -1;
	}
	ds18b20WriteOneByte(me, 0xcc);
	ds18b20WriteOneByte(me, 0x44);

	return 0;
}

static float ds18b20_readtemp(struct ds18b20* const me)
{
	if(ds18b20Reset(me) != 0)
        {
                printf("not found sensor feedback!\n");
                return -1;
        }
	ds18b20WriteOneByte(me, 0xcc);
        ds18b20WriteOneByte(me, 0xbe);
	unsigned int dat = ds18b20ReadOneByte(me) + (ds18b20ReadOneByte(me) * 256);
	if(dat > 0x6000)
	{
		dat = ~dat +1;
	}
	float tmp = dat * 0.0625;
    if(tmp < DS18B20_MAX_TMP && tmp > DS18B20_MIN_TMP)
    {
        me->last_tmp = tmp;
        return tmp;
    }
    else
    {
        return me->last_tmp;
    }
}

static int ds18b20_init(struct ds18b20 *me, u32 BASEADDR, int channel, int pin, 
			int   (*transform)(struct ds18b20* const me), 
			float (*readtemp)(struct ds18b20* const me))
{
    memset(me, 0, sizeof(struct ds18b20));
    me->DQ = XilGpioCreate(BASEADDR);
	me->channel = channel;
    me->pin = pin;
    me->transform = transform;
    me->readtemp = readtemp;
    me->DQ->modeWrite(me->DQ, me->channel, me->pin, XIL_OUTPUT);
    me->DQ->digitalWrite(me->DQ, me->channel, me->pin, 1);
    return 0;
}

struct ds18b20 *ds18b20Create(u32 BaseAddr, int channel, int pin)
{
	struct ds18b20 *me = (struct ds18b20 *)malloc(sizeof(struct ds18b20));
	if(me == NULL)
	{
		printf("ds18b20 create failed!\n");
		return me;
	}
	memset(me, 0, sizeof(struct ds18b20));
	ds18b20_init(me, BaseAddr, channel, pin, ds18b20_transform, ds18b20_readtemp);
	return me;
}

int ds18b20Destory(struct ds18b20 *me)
{
	if(me != NULL)
	{
		XilGpioDestroy(me->DQ);
		free(me);
	}

	return 0;
}
