#ifndef _Plane_H
#define _Plane_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Object
{
	Vect normal;
	double distance;
	Color color;

public:
	Plane(Vect normalValue, double distanceValue, Color colorValue)
	{
		normal = normalValue;
		distance = distanceValue;
		color = colorValue;
	}

	// method functions
	Vect getPlaneNormal() { return normal; }
	double getPlaneDistance() { return distance; }
	virtual Color getColor() { return color; }

	virtual Vect getNormalAt(Vect point)
	{
		return normal;
	}

	virtual double findIntersection(Ray ray)
	{
		Vect ray_direction = ray.getRayDirection();

		double a = ray_direction.dotProduct(normal);

		// se o ray nao for paralelo ao plano
		if (a != 0)
		{
			double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
			return -1 * b / a;
		}

		return -1;
	}
};

#endif
