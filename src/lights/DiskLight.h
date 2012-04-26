#ifndef DISKLIGHT_H_
#define DISKLIGHT_H_

#include "Light.h"

class DiskLight: public Light {
public:
	DiskLight(	const SpectralQuantity &intensity,
				const Vec3 &centre,
				const Vec3 &normal,
				float radius);

	virtual SpectralQuantity getIntensity(const Vec3 &from);

	// Métodos de Object
    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

    virtual SpectralQuantity computeLocalShading(const Intersection& intersection,
												const SpectralQuantity& intensity,
												const Vec3& toLight,
												const Vec3& toView);

private:
    Vec3 centre;
    float radius;

    Vec3 xVec;
    Vec3 yVec;
};

#endif /* DISKLIGHT_H_ */
