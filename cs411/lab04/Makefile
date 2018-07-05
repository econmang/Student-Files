#
# Makefile
# CS411 Lab 4
# Kevin Sahr
# February 21, 2017
#

CFLAGS = -Wall -g

all : listMenu

listMenu : listMenu.o itemList.o itemLL.o
	gcc -o listMenu listMenu.o itemList.o itemLL.o

listMenu.o : listMenu.c itemList.h
	gcc ${CFLAGS} -c listMenu.c 

itemList.o : itemList.c itemList.h
	gcc ${CFLAGS} -c itemList.c 

itemLL.o : itemLL.c itemLL.h
	gcc ${CFLAGS} -c itemLL.c 

clean :
	rm -rf listMenu listMenu.o itemList.o itemLL.o core 
