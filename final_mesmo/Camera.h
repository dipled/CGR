#ifndef _Camera_H
#define _Camera_H

#include "Vect.h"

class Camera
{
public:
	Vect posCam, dirCam, camright, camdown;

	Camera(Vect pos, Vect dir, Vect right, Vect down)
	{
		posCam = pos;
		dirCam = dir;
		camright = right;
		camdown = down;
	}
};

#endif
