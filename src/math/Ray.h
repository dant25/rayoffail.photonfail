#ifndef RAY_H_
#define RAY_H_

#include "Vec3.h"

class Ray { 
public:
	Ray(const Vec3 &origin, const Vec3 &dir){
		d = dir;
		o = origin;
	}

    Ray() { };

    //vetor direção
    Vec3 d;
    //posição de origem
    Vec3 o;
};


#endif

