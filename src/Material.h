#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "SpectralQuantity.h"
#include "Texture.h"
class Material {
public:
    Material(const SpectralQuantity& kd, 
             const SpectralQuantity& ks,
             const SpectralQuantity& ka,
             float shininess,
             float spec);

    SpectralQuantity kd, ks, ka;
    float shininess;
    float spec;

   Texture *tex;
};

#endif
