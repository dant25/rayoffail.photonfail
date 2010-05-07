#ifndef SPEHERE_H_
#define SPEHERE_H_

#include "Object.h"

class Sphere : public Object {
public:
    Sphere(float radius, Vec3 center);
    bool intersect(const Ray& r);
    SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                         const SpectralQuantity& diffuse,
                                         const SpectralQuantity& specular,
                                         const SpectralQuantity& ambient) const;
private:
    float radius;
    Vec3 c;
    
};

#endif
