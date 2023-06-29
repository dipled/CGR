#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include "Object.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;
	
	public:

	Sphere (Vect centerValue, double radiusValue, Color colorValue) {
		center = centerValue;
		radius = radiusValue;
		color = colorValue;
	}
	
	// Todas as funções da classe:
	Vect getSphereCenter () { return center; }
	double getSphereRadius () { return radius; }
	virtual Color getColor () { return color; }
	
	virtual Vect getNormalAt(Vect point) {
		// A normal sempre aponta para fora a partir do centro da esfera, logo, para um dado ponto P na...
		// ... esfera, sendo C o centro da esfera, tem-se n = P-C:
		Vect normal_Vect = point.vectAdd(center.negative()).normalize();
		return normal_Vect;
	}
	
	// Encontra se o raio tem interseção com a esfera:
	virtual double findIntersection(Ray ray) {

		// r = |(t*direcao + origem) - C|
		// (t*direcao + origem) - C = (t*Xd + Xo - Xc, t*Yd + Yo - Yc, t*Zd + Zo - Zc)
		// sqrt( (t*Xd + (Xo - Xc))² + (t*Yd + (Yo - Yc))² + (t*Zd + (Zo  -Zc))²)
		// sqrt( (t*Xd)² + 2(t*Xd)(Xo - Xc) + (Xo - Xc)² + (t*Yd)² + 2(t*Yd)(Yo - Yc) + (Yo - Yc)² + (t*Zd)² + 2(t*Zd)(Zo - Zc) + (Zo - Zc)² )
		// sqrt( (t*Xd)² + (t*Zd)² + (t*Yd)² + 2(t*Xd)(Xo - Xc) + 2(t*Yd)(Yo - Yc) + 2(t*Zd)(Zo - Zc) + (Xo - Xc)² + (Yo - Yc)² + (Zo - Zc)²)
		// Para que haja interseção 
		// r² = |(t*direcao + origem) - C|²
		// r² = (t*Xd)² + (t*Zd)² + (t*Yd)² + 2(t*Xd)(Xo - Xc) + 2(t*Yd)(Yo - Yc) + 2(t*Zd)(Zo - Zc) + (Xo - Xc)² + (Yo - Yc)² + (Zo - Zc)²
		// 0 = (t*Xd)² + (t*Zd)² + (t*Yd)² + 2(t*Xd)(Xo - Xc) + 2(t*Yd)(Yo - Yc) + 2(t*Zd)(Zo - Zc) + [(Xo - Xc)² + (Yo - Yc)² + (Zo - Zc)² - r²]
		// 0 = t² *(Xd² + Yd² + Zd²) + t*2*[(Xd)(Xo - Xc) + (Yd)(Yo - Yc) + (Zd)(Zo - Zc)] + [(Xo - Xc)² + (Yo - Yc)² + (Zo - Zc)² - r²]
		// Podemos resolver usando Bháskara:
		// Δ = b² - 4.a.c, onde 
		// b = 2*[(Xd)(Xo - Xc) + (Yd)(Yo - Yc) + (Zd)(Zo - Zc)],
		// a = (Xd² + Yd² + Zd²),
		// c = [(Xo - Xc)² + (Yo - Yc)² + (Zo - Zc)² - r²]
		// Portanto:
		// t = (-b ± √Δ)/(2a)

		Vect ray_origin = ray.getRayOrigin();
		double ray_origin_x = ray_origin.getVectX();
		double ray_origin_y = ray_origin.getVectY();
		double ray_origin_z = ray_origin.getVectZ();
		
		Vect ray_direction = ray.getRayDirection();
		double ray_direction_x = ray_direction.getVectX();
		double ray_direction_y = ray_direction.getVectY();
		double ray_direction_z = ray_direction.getVectZ();
		
		Vect sphere_center = center;
		double sphere_center_x = sphere_center.getVectX();
		double sphere_center_y = sphere_center.getVectY();
		double sphere_center_z = sphere_center.getVectZ();
		
		// Como o vetor de direção é sempre unitário (pela normalização) o valor de a será sempre igual à 1:
		// double a = (pow(ray_direction_x, 2) + pow(ray_direction_y, 2) + pow(ray_direction_z, 2));
		double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
		double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius*radius);
		
		double discriminant = b*b - 4*c/*a*/;

		//Se o discriminant for positivo, tem interseção e é calculado o menor valor		
		if (discriminant > 0) {
			/// the ray intersects the sphere
			
			// the first root
			double root_1 = ((-1*b - sqrt(discriminant))/2)- 0.000001; //esse 0.000001 serve para deixar um pouco fora da esfera...
			// ... pois senão a reflexão de um raio pode "rebater" superfície da esfera (intersecção em t = 0 do raio refletido)
			
			if (root_1 > 0) {
				// the first root is the smallest positive root
				return root_1;
			}
			else {
				// the second root is the smallest positive root
				double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001; //esse 0.000001 serve para deixar um pouco fora da esfera...
				// ... pois senão a reflexão de um raio pode "rebater" superfície da esfera (intersecção em t = 0 do raio refletido)
				return root_2;
			}
		}
		else {

			return -1;
		}
	}
	
};



#endif
