#ifndef PARTICULAS_H
#define PARTICULAS_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
typedef struct particula
{
	double tempoVida;
    double pos_x;
    double pos_y; 
    double pos_z; 
    double velocidade;
    double raio;
    double gravidade;
    int vivo;

}Particula;

#endif