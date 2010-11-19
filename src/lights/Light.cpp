#include "Light.h"

#include <iostream>

using namespace std;


Light::Light(const SpectralQuantity &intensity)
:	Object(Material(intensity, intensity, intensity, 0.0, 0.0)),
	intensity(intensity)
{
}

SpectralQuantity Light::getIntensity(const Vec3 &/*from*/) {
    return intensity;
}

/*
SpectralQuantity Light::computeLocalShading(const Intersection& lIntersect, const SpectralQuantity& intensity, const Vec3& rayOrigin)
{
	cout << "Shading on light surface!" << endl;
	return this->intensity + intensity;
}
*/
