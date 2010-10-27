#include "PointLight.h"

PointLight::PointLight(const Vec3 &pos, const SpectralQuantity &intensity)
:	Light(intensity),
 	position(pos)
{
}


bool PointLight::intersect(const Ray& r, Intersection &i){
	return false;
}


Vec3 PointLight::samplePoint() {
    return this->position;
}


void PointLight::getNormal(Vec3 point, Vec3 &normal) {
}
