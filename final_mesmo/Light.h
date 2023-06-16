#ifndef _Light_H
#define _Light_H

#include "Vect.h"
#include "Color.h"

class Light
{
public:
	Vect posLuz;
	Color corLuz;

	Light(Vect p, Color c)
	{
		posLuz = p;
		corLuz = c;
	}
};

#endif