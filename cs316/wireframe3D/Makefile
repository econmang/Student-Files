EXEC = wireframe
SRCS = ${EXEC}.c glfuncs.c shader.c matrix.c
OBJS = ${EXEC}.o glfuncs.o shader.o matrix.o
INCDIRS = 
CCFLAGS  = ${INCDIRS} -Wno-deprecated-declarations -Wall
#LDLIBS= -framework OpenGL -framework Glut
LDLIBS = -lGL -lGLU -lglut -lm
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

