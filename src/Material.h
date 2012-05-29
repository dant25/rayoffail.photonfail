#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Vec3.h"
#include "SpectralQuantity.h"
#include "Texture.h"

enum ReflectivityType { SPECULAR, DIFFUSE};

class Material {
public:
    Material(const SpectralQuantity& kd, 
             const SpectralQuantity& ks,
             const SpectralQuantity& ka,
             float shininess,
             float spec);
    
    SpectralQuantity sampleBRDF(Vec3 n, Vec3 indir, Vec3 *dir, ReflectivityType &rt);

    SpectralQuantity kd, ks, ka;
    float shininess;
    float spec;

    Texture *tex;
};

#endif
