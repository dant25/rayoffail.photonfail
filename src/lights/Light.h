#ifndef LIGHT_H_
#define LIGHT_H_

#include "../math/Intersection.h"
#include "../SpectralQuantity.h"

class Light {
public:
    Light(const SpectralQuantity &intensity);

    virtual Vec3 samplePoint() = 0;
    virtual void getNormal(Vec3 point, Vec3 &normal) = 0;

    SpectralQuantity getIntensity();


protected:
    SpectralQuantity intensity;
};

#endif
