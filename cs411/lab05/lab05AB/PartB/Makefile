#
# Makefile
# CS411 Lab 1
# Evan Conley
# March 18, 2017
#

# my variables
EXEC = graphMenu
FUNCS = airGraph
OBJS = ${EXEC}.o ${FUNCS}.o vertexLL.o vertexQ.o
HDRS = ${FUNCS}.h airport.h vertex.h vertexLL.h vertexQ.h

# implicit rules variables
CFLAGS = -g -Wall
# LDFLAGS = 
CC = gcc 

all : ${EXEC}

${EXEC} : ${OBJS}

${OBJS} : ${HDRS}

clean :
	rm -rf ${EXEC} ${OBJS} core 