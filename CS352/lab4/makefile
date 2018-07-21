#
# Makefile for evalit program
# Pete Nordquist
#

OBJS = evalit.tab.o evalit.o 

GENFILES = evalit.tab.c evalit.tab.h evalit.output evalit.c

evalit: $(OBJS)
	gcc -gstabs1 -o evalit $(OBJS)

evalit.tab.o: evalit.tab.h evalit.tab.c
	gcc -c -gstabs1 -DYYDEBUG evalit.tab.c

evalit.tab.h: evalit.y
	bison -d -v evalit.y

evalit.o: evalit.c
	gcc -c -gstabs1 evalit.c

evalit.c: evalit.tab.h evalit.l
	flex -oevalit.c evalit.l

clean:
	-rm evalit $(OBJS) $(GENFILES)

.PHONY: clean