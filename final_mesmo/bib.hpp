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

Vect posCam(-10, 0, -10);
Vect posLuz(0, 2, 1);
Vect look_at(0, 0, 0);

Color white_light(1.0, 1.0, 1.0, 0);
Color pretty_green(0.5, 1.0, 0.5, .3);
Color maroon(0.5, 0.25, 0.25, 0.8);
Color red(1.0, 0.2, 0.1, 0.3);
Color tile_floor(1, 1, 1, 2);
Color gray(0.5, 0.5, 0.5, 0);
Color black(0.0, 0.0, 0.0, 0.3);
Color green(0.0, 1.0, 0.0, 0.3);
Color blue(0.1, 0.1, 1.0, 0);
Color cool_blue(0.1, 0.3, 1.0, 0.4);
Color full_white(1, 1, 1, .3);

// Objetos presentes na cena
Sphere sphere_1(Vect(1, 0, 0), 1, pretty_green);
Sphere sphere_2(Vect(3, 0, 3), .75, cool_blue);
Sphere sphere_3(Vect(0, 1, -2), 0.7, white_light);
Sphere sphere_4(Vect(-4.5, 1, 4), 1, maroon);
//Sphere sphere_5(Vect(2, 3, 7), 3.7, maroon);

Sphere sphere_6(Vect(-5, 3, 0), 1, full_white);
Sphere sphere_7(Vect(-3, 3, 0), 1, full_white);
Sphere sphere_8(Vect(-1, 3, 0), 1, full_white);
Sphere sphere_9(Vect(1, 3, 0), 1, full_white);
Sphere sphere_10(Vect(3, 3, 0), 1, full_white);
Sphere sphere_11(Vect(5, 3, 0), 1, full_white);

//Plano
Plane ground(Y, -1, red);
Plane wall(Vect(1, 0, -1), -10, blue);
Plane wall_2(Vect(0, 0, -3), -10, Color(0,1,0,0));
Plane wall_3(Vect(0, 0, 3), -10, Color(0.9, 0.3, 0.8, 0));

#endif