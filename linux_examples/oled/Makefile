###########################################
#Makefile for simple programs
###########################################
CFLAGS += -I../xlib/
LIB= 

CC=gcc
CC_FLAG=-Wall 

PRG=oled
OBJ=main.o xil_oled.o  ../xlib/xil_wrapper.o ../xlib/xil_spi.o ../xlib/xil_gpio.o ../xlib/xil_io.o

$(PRG):$(OBJ)
	$(CC)  -o $@ $(OBJ) $(INC) $(LIB)
	
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC)  -c $*.cpp -o $*.o $(INC) $(LIB)

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
