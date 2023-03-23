CC = gcc
FLAGS = -c -Wall
LIBS = -lglut -lGL -lGLU -lm 
all: robo castelo bonecoDeNeve

clean:
	rm  *.out *.o

casteloC: 
	${CC} ${FLAGS} castelo.c

castelo: casteloC
	${CC}  castelo.o ${LIBS} -o castelo.out

bonecoDeNeve: bonecoDeNeveC
	${CC} bonecoDeNeve.o ${LIBS} -o bonecoDeNeve.out

bonecoDeNeveC:
	${CC} ${FLAGS} bonecoDeNeve.c

robo: roboC
	${CC} robo.o ${LIBS} -o robo.out

roboC:
	${CC} ${FLAGS} robo.c 
