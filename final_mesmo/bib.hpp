 #ifndef _BIB_HPP
#define _BIB_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include <unistd.h>
using namespace std;

int thisone;
int dpi = 72;
// int aadepth = 1;
double aathreshold = 0.1;
double luzAmbiente = 0.2;
double acuracia = 0.00000001;

Vect O(0, 0, 0); //vetor origem
Vect X(1, 0, 0); //Vetor i
Vect Y(0, 1, 0); //Vetor j
Vect Z(0, 0, 1); //Vetor k

Vect posCam(0, 1, -22);
Vect posLuz(0, 7, 10);
Vect look_at(1, 0, -7);

Color white_light(1.0, 1.0, 1.0, 0);
Color pretty_green(0.5, 1.0, 0.5, 1);
Color maroon(0.5, 0.25, 0.25, 0.8);
Color red(1.0, 0.2, 0.1, 0.3);
Color tile_floor(1, 1, 1, 1);
Color gray(0.5, 0.5, 0.5, 0);
Color black(0.0, 0.0, 0.0, 0.8);
Color green(0.0, 0.7, 0.4, 0.2);
Color blue(0.5, 0.5, 0.9, 0);
Color purple(0.4, 0, 0.7, 0.2);
Color cool_blue(0.1, 0.3, 1.0, 0.2);
Color full_white(1, 1, 1, 0.1);
Color sky_blue(	0.529, 0.808, 0.922, 0.1);

// Objetos presentes na cena
Sphere sphere_1(Vect(0, 0, 0), 0.2, full_white);
Sphere sphere_2(Vect(-5, 2, -2), .4, full_white);
Sphere sphere_3(Vect(0, 1, -2), 0.7, full_white);
Sphere sphere_4(Vect(-4.5, 1, 4), 1, full_white);
// Sphere sphere_5(Vect(2, 3, 7), 3.7, maroon);

Sphere sphere_6(Vect(1, 7, 0), 1, purple);
Sphere sphere_7(Vect(-1, 5, 0), 1, black);
Sphere sphere_8(Vect(0, 2, -1), 1, green);
Sphere sphere_9(Vect(0, 2, 1), 1, red);


Sphere sphere_10(Vect(3, 3, 0), 1, full_white);
Sphere sphere_11(Vect(5, 3, 0), 1, full_white);

//Plano
Plane ground(Y, -1, sky_blue);
Plane wall(Vect(-1, 0, 0), 20, sky_blue);
Plane wall_2(Vect(0, 0, 1), 20, green);
// Plane wall_3(Vect(0, 0, -1), 20, gray);

#endif