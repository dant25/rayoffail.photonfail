#ifndef SQUARELIGHT_H_
#define SQUARELIGHT_H_

#include "Light.h"

class QuadLight: public Light {
public:
	QuadLight(	const SpectralQuantity &intensity,
				const Vec3 &centre,
				const Vec3 &at_width,
				const Vec3 &at_height);

	// Métodos de Object
    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

    virtual SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                         const SpectralQuantity& intensity,
                                         const Vec3& rayOrigin);

private:
    Vec3 centre;
    Vec3 at_width;
    Vec3 at_height;

    float width;
    float height;
};

#endif /* SQUARELIGHT_H_ */
