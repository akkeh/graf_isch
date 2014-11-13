CC=g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

OBJ = animation.o

all: tut

tut: ${OBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ} ${LIBS}

.cpp.p:
	${CC} -c $< ${CFlAGS} ${LIBS}

clean:
	rm -rf *.o
