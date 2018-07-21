EXEC = lab8
SRCS = ${EXEC}.c glfuncs.c shader.c matrix.c
OBJS = ${EXEC}.o glfuncs.o shader.o matrix.o
INCDIRS = 
CCFLAGS  = -g ${INCDIRS} -Wno-deprecated-declarations -Wall
LDLIBS= -framework OpenGL -framework Glut
COMP = gcc

ALLOBJS = ${OBJS}

all: ${EXEC}

${EXEC}: ${ALLOBJS}
	${COMP} $(CCFLAGS) $(EXPORT) -o ${EXEC} ${ALLOBJS} $(LDLIBS)

.c.o:
	${COMP} -c $< $(CCFLAGS)

link:
	${COMP} $(CCFLAGS) $(EXPORT) -o ${EXEC} ${ALLOBJS} $(LDLIBS)

clean:
	rm -rf *.o ${EXEC} core

depend:
	makedepend ${INCDIRS} -I/ ${SRCS}

# DO NOT DELETE THIS LINE -- make depend depends on it.

