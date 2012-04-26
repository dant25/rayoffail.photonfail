#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "Light.h"

class SpotLight: public Light {
public:
	SpotLight(	const SpectralQuantity &intensity,
				const Vec3 &position,
				const Vec3 &direction,
				float cutoff,
				float exp);

	virtual SpectralQuantity getIntensity(const Vec3 &from);

	// Métodos de Object
    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

private:
    Vec3 position;
    Vec3 direction;
    float cutoff;
    float exp;
};

#endif /* SPOTLIGHT_H_ */
