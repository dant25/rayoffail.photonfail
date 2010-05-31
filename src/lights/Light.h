#ifndef LIGHT_H_
#define LIGHT_H_

#include "../math/Intersection.h"
#include "../SpectralQuantity.h"

#include "../objects/Object.h"

class Light: public Object{
public:
    Light(const SpectralQuantity &intensity);

    virtual SpectralQuantity getIntensity(const Vec3 &from);

protected:
    SpectralQuantity intensity;
};

#endif
