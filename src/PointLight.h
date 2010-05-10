#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(SpectralQuantity diffuse, SpectralQuantity specular, SpectralQuantity ambient);

    Vec3 samplePoint();
    void getNormal(Vec3 point, Vec3 &normal);
    
    Vec3 pos;
};


#endif
