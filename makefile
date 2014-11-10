CC=g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

OBJ = base.o

all: base

base: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ} ${LIBS}

.cpp.p:
	${CC} -c $< ${CFlAGS} ${LIBS}

clean:
	rm -rf *.o
