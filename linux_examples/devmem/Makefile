###########################################
#Makefile for simple programs
###########################################
INC=
LIB= 

CC=gcc
CC_FLAG=-Wall 

PRG=devmem
OBJ=devmem.o 

$(PRG):$(OBJ)
	$(CC)  -o $@ $(OBJ) $(INC) $(LIB)
	
.SUFFIXES: .c .o .cpp
.cpp.o:
	$(CC)  -c $*.cpp -o $*.o $(INC) $(LIB)

.PRONY:clean
clean:
	@echo "Removing linked and compiled files......"
	rm -f $(OBJ) $(PRG)
