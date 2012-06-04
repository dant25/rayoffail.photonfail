#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const Vec3 &pos, const SpectralQuantity &intensity);

    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);
    virtual Vec3 sampleDir(); 
    

    Vec3 position;
};


#endif
