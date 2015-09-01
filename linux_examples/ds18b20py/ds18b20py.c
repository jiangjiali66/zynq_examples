/*
 * =====================================================================================
 *
 *       Filename:  ds18b20py.c
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
#include <Python.h>
//#define DQ_BASE_ADDR    0x41210000
//#define DQ_PIN          0
//#define DQ_CHANNEL      GPIO_CH1

struct ds18b20* ds18b20_sensor;

int ds18b20_init(u32 base_addr, int ch, int pin)
{
	ds18b20_sensor = ds18b20Create(base_addr, ch, pin);
	if(ds18b20_sensor == NULL)
	{
		return -1;
	}

	return 0;
}

float ds18b20_transform()
{
    if(ds18b20_sensor->transform(ds18b20_sensor) != 0)
    {
        return 0;
    }
    sleep(1);
    return ds18b20_sensor->readtemp(ds18b20_sensor);
}

int ds18b20_exit()
{
    ds18b20Destory(ds18b20_sensor);
}

PyObject* ds18b20_init_fact(PyObject* self, PyObject* args) 
{
  int n[3], result;
  
  if (! PyArg_ParseTuple(args, "iii", &n[0], &n[1], &n[2]))
  printf("%d\n", n[0]);
  result = ds18b20_init(n[0], n[1], n[2]);
  return Py_BuildValue("i", result);
}

PyObject* ds18b20_transform_fact(PyObject* self, PyObject* args)
{
   float result;
   result = ds18b20_transform();
   return Py_BuildValue("f", result);
}

PyObject* ds18b20_exit_fact(PyObject* self, PyObject* args)
{
    ds18b20_exit();
    return Py_BuildValue("i", 0);
}



static PyMethodDef ds18b20Methods[] = 
{
  {"init", 	ds18b20_init_fact, 	METH_VARARGS, "Caculate N!"},
  {"transform", ds18b20_transform_fact, METH_VARARGS, "Caculate N!"},
  {"exit", 	ds18b20_exit_fact, 	METH_VARARGS, "Caculate N!"},
  {NULL, NULL}
};

void initds18b20() 
{
  PyObject* m;
  m = Py_InitModule("ds18b20", ds18b20Methods);
}
