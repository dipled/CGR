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
	
	// Todas as funções da classe:
	Vect getPlaneNormal () { return normal; }
	double getPlaneDistance () { return distance; }
	virtual Color getColor () { return color; }
	
	// A normal do plano sobre qualquer ponto do plano é sempre igual:
	virtual Vect getNormalAt(Vect point) {
		return normal;
	}
	
	// Note que a intersecção entre um objeto qualquer e um raio é uma constante b tal que o vetor de direção...
	// ... do raio multiplicado por b resulta no ponto em que a reta dada por este vetor e sua origem intersecta o objeto: 
	virtual double findIntersection(Ray ray) {
		Vect ray_direction = ray.getRayDirection();
		
		// Produto escalar n . r, onde n é a normal ao plano e r é o vetor de direção do raio:
		double a = ray_direction.dotProduct(normal);
		
		// Se o raio não for paralelo ao plano (se fosse paralelo não poderia incidir):
		if(a != 0) {
			Vect p0 = normal.vectMult(distance);
			Vect l0 = ray.getRayOrigin();

			// Sendo r o vetor de direção do raio, n a normal ao plano, p0 o ponto cujo a reta da pelo...
			// ... vetor n incide no plano, l0 a origem do raio, a equação é dada por:
			// t = (p0 - l0). n / (n . r)
			return (p0.vectAdd(l0.negative())).dotProduct(normal)/a - 0.00000000001;
			// Explicação detalhada em: 
			// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
		}

		// Caso não haja intersecção (a intersecção nunca estará na direção contrária do raio):
		return -1;
	}
	
};


#endif
