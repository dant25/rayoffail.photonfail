#ifndef OBJECT_H_
#define OBJECT_H_

#include "../math/Ray.h"
#include "../math/Intersection.h"
#include "../SpectralQuantity.h"

class Object {
public:
    virtual bool intersect(const Ray& r) = 0;
    virtual SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                                 const SpectralQuantity& diffuse,
                                                 const SpectralQuantity& specular,
                                                 const SpectralQuantity& ambient) const = 0;
    Intersection getIntersection();
protected:
    //Armazena o último ponto de interseção
    Intersection i;
};

#endif
