CC = gcc
FLAGS = -c -Wall
LIBS = -lglut -lGL -lGLU -lm 
all: neve fogo

clean:
	rm  *.out *.o

neve: neveC
	${CC} neve.o ${LIBS} -o neve.out

neveC:
	${CC} ${FLAGS} neve.c
fogo: fogoC
	${CC} fogo.o ${LIBS} -o fogo.out

fogoC:
	${CC} ${FLAGS} fogo.c
lavaC:
	${CC} ${FLAGS} lava.c

lava: lavaC
	${CC} lava.o ${LIBS} -o lava.out
particleC:
	${CC} ${FLAGS} particle.c

particle: particleC
	${CC} particle.o ${LIBS} -o particle.out