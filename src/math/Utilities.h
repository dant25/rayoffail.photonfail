#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <cstdlib>

#define RAND(inf, sup) (inf + ((((sup)-(inf))/(float)RAND_MAX)*rand()))
#define PROB(prob) (rand() < ((prob)*(RAND_MAX-1)))
#define MAX(x, y) ((x)<(y)?(y):(x))


#endif /* UTILITIES_H_ */
