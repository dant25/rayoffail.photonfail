#ifndef OBJECT_H_
#define OBJECT_H_

#include "../math/Ray.h"
#include "../math/Intersection.h"
#include "../SpectralQuantity.h"
#include "../Material.h"

class Object {
public:
    Object(const Material& mat);
    virtual bool intersect(const Ray& r) = 0;
    SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                         const SpectralQuantity& intensity,
                                         const Vec3& rayOrigin);
    Intersection getIntersection();
protected:
    //Armazena o último ponto de interseção
    Intersection i;
    Material m;
};

#endif
