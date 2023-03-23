CC = gcc
FLAGS = -c -Wall
LIBS = -lglut -lGL -lGLU -lm 
all: robo castelo bonecoDeNeve

robo: 
	${CC} robo.c ${LIBS} -o robo.out
clean:
	rm  *.out
castelo:
	${CC} castelo.c ${LIBS} -o castelo.out
bonecoDeNeve:
	${CC} bonecoDeNeve.c ${LIBS} -o bonecoDeNeve.out

