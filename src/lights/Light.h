#ifndef LIGHT_H_
#define LIGHT_H_

#include "../math/Intersection.h"
#include "../SpectralQuantity.h"

#include "../objects/Object.h"

class Light: public Object{
public:
    Light(const SpectralQuantity &intensity);

    virtual SpectralQuantity getIntensity(const Vec3 &from);
    inline Vec3 getIntensity() { 
        return Vec3(intensity.data[0], intensity.data[1], intensity.data[2]); 
    }

    //Amostra uma direção vinda da luz
    virtual Vec3 sampleDir();

protected:
    SpectralQuantity intensity;
};

#endif
