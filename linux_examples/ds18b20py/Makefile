###########################################
#Makefile for simple programs
###########################################
CFLAGS += -I../xlib/ -I/usr/include/python2.7/ -fPIC
LIB= 

CC=gcc
 
LDFLAGS = -shared

PRG=ds18b20
TARGET_LIB = $(PRG).so
OBJ=ds18b20py.o ds18b20.o  ../xlib/xil_io.o ../xlib/xil_gpio.o

$(TARGET_LIB):$(OBJ)
	$(CC) ${LDFLAGS} -o $@ $(OBJ) $(INC) $(LIB)
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC)  -c $*.cpp -o $*.o $(INC) $(LIB)
	

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
