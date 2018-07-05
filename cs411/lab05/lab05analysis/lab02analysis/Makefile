#
# Makefile
# CS411 Lab 2
# Evan Conley
# January 30, 2017
#

# my variables
EXEC = listDriver
FUNCS = itemList
OBJS = ${EXEC}.o ${FUNCS}.o
HDRS = ${FUNCS}.h

# implicit rules variables
CFLAGS = -g -Wall
# LDFLAGS = 
CC = gcc 

all : ${EXEC}

${EXEC} : ${OBJS}

${OBJS} : ${HDRS}

clean :
	rm -rf ${EXEC} ${OBJS} core 
