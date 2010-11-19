

#include "SpotLight.h"

#include <cmath>


SpotLight::SpotLight(	const SpectralQuantity &intensity,
						const Vec3 &position,
						const Vec3 &direction,
						float cutoff,
						float exp)
:	Light(intensity),
 	position(position),
 	direction(direction),
 	cutoff(cutoff),
 	exp(exp)
{
}


SpectralQuantity SpotLight::getIntensity(const Vec3 &from){
	float c_ang = direction.dot(from);

	if(acos(c_ang) > cutoff)
		return SpectralQuantity();

	return intensity*pow(c_ang, exp);
}


bool SpotLight::intersect(const Ray& /*r*/, Intersection &/*i*/) {
	return false;
}


Vec3 SpotLight::samplePoint(){
	return position;
}


void SpotLight::getNormal(Vec3 /*point*/, Vec3 &/*norm*/){
}
