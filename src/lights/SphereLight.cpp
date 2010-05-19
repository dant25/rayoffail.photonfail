
#include "SphereLight.h"

#include <iostream>

using namespace std;

SphereLight::SphereLight(const SpectralQuantity &intensity, const Vec3 &centre, float radius)
:	Light(intensity),
	sphere(m, radius, centre)
{
}


bool SphereLight::intersect(const Ray& r){
	return sphere.intersect(r);
}


Vec3 SphereLight::samplePoint(){
	return sphere.samplePoint();
}


void SphereLight::getNormal(Vec3 point, Vec3 &normal){
	sphere.getNormal(point, normal);
}


SpectralQuantity SphereLight::computeLocalShading(const Intersection& lIntersect, const SpectralQuantity& intensity, const Vec3& rayOrigin)
{
	cout << "Shading on light surface!" << endl;

	return this->intensity + sphere.computeLocalShading(lIntersect, intensity, rayOrigin);
}
