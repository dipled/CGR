#ifndef _Plane_H
#define _Plane_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Object {
	Vect normal;
	double distance;
	Color color;
	
	public:
	
	Plane (Vect normalValue, double distanceValue, Color colorValue) {
		normal = normalValue;
		distance = distanceValue;
		color = colorValue;
	}

	
	// method functions
	Vect getPlaneNormal () { return normal; }
	double getPlaneDistance () { return distance; }
	virtual Color getColor () { return color; }
	
	virtual Vect getNormalAt(Vect point) {
		return normal;
	}
	
	// Note que a intersecção entre um objeto qualquer e um raio é uma constante b tal que o vetor de direção...
	// ... do raio multiplicado por b resulta no ponto em que a reta dada por este vetor e sua origem intersecta o objeto: 
	virtual double findIntersection(Ray ray) {
		Vect ray_direction = ray.getRayDirection();
		
		// Produto escalar n . direção:
		double a = ray_direction.dotProduct(normal);
		
		// Se o ray nao for paralelo ao plano
		if(a != 0) {
			Vect p0 = normal.vectMult(distance);
			Vect l0 = ray.getRayOrigin();
			return (p0.vectAdd(l0.negative())).dotProduct(normal)/a;
			// Explicação detalhada em: 
			// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
		}

		// Caso não haja intersecção:
		return -1;
	}
	
};


#endif
