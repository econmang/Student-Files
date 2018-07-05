#
# Makefile
# CS411 Lab 1
# Kevin Sahr
# January 10, 2017
#

# my variables
EXEC = listMenu
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
