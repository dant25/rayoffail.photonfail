#ifndef SPHERELIGHT_H_
#define SPHERELIGHT_H_

#include "Light.h"

#include "../objects/Sphere.h"

class SphereLight: public Light {
public:
	SphereLight(const SpectralQuantity &intensity, const Vec3 &centre, float radius);

	// Métodos de Object
    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

    virtual SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                         const SpectralQuantity& intensity,
                                         const Vec3& rayOrigin);

private:
    Sphere sphere;
};

#endif /* SPHERELIGHT_H_ */
