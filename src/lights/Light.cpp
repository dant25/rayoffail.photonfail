#include "Light.h"

#include <iostream>

using namespace std;


Light::Light(const SpectralQuantity &intensity)
:	Object(Material(intensity, intensity, intensity, 0.0, 0.0)),
	intensity(intensity)
{
}

SpectralQuantity Light::getIntensity(const Vec3 &from) {
    return intensity;
}

Vec3 Light::sampleDir() {
    return Vec3(0.f, 0.f, 0.f);
}

/*
SpectralQuantity Light::computeLocalShading(const Intersection& lIntersect, const SpectralQuantity& intensity, const Vec3& rayOrigin)
{
	cout << "Shading on light surface!" << endl;
	return this->intensity + intensity;
}
*/
