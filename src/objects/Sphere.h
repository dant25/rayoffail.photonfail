#ifndef SPEHERE_H_
#define SPEHERE_H_

#include "Object.h"

class Sphere : public Object {
public:
    Sphere(const Material& mat, float radius, Vec3 center);
    bool intersect(const Ray& r);
private:
    float radius;
    Vec3 c;
    
};

#endif
