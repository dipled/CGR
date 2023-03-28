#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray {
	
	public:
	Vect origin, direction;
	
	Ray () {
		origin = Vect(0,0,0);
		direction = Vect(1,0,0);
	}

	Ray (Vect o, Vect d) {
		origin = o;
		direction = d;
	}
	
	// method functions
	Vect getRayOrigin () { return origin; }
	Vect getRayDirection () { return direction; }
	
};



#endif
