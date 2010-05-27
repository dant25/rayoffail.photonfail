#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cstdlib>
#include <cmath>
#include "Vec3.h"

#define RAND(inf, sup) (inf + ((((sup)-(inf))/(float)RAND_MAX)*rand()))
#define PROB(prob) (rand() < ((prob)*(RAND_MAX-1)))
#define MAX(x, y) ((x)<(y)?(y):(x))

void barycentricCoords(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p,
                       float &l1, float &l2, float &l3);

float strToFloat(const char *);

#endif /* UTILITIES_H_ */
