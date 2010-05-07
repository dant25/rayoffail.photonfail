#ifndef LIGHT_H_
#define LIGHT_H_

#include "math/Intersection.h"
#include "SpectralQuantity.h"

class Light {
public:
    Light(SpectralQuantity diffuse, SpectralQuantity specular, SpectralQuantity ambient);

    virtual Vec3 samplePoint() = 0;
    virtual void getNormal(Vec3 point, Vec3 &normal) = 0;

    SpectralQuantity getDiffIntensity();
    SpectralQuantity getSpecIntensity();
    SpectralQuantity getAmbIntensity();

protected:
    SpectralQuantity diff, spec, amb;
};

#endif
