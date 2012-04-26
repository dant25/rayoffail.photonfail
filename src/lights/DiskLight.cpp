
#include "DiskLight.h"

#include <cmath>
#include "../math/Utilities.h"


DiskLight::DiskLight(	const SpectralQuantity &intensity,
						const Vec3 &centre,
						const Vec3 &normal,
						float radius)
:	Light(intensity),
 	centre(centre),
 	radius(radius)
{
	i.normal = normal;

	// Obtem uma sistema de coordenadas com z = normal
	// FIXME: Tem um jeito melhor de fazer isso?
	Vec3 aux = i.normal;
	aux.x += 1.0;
	aux.y += 1.0;
	aux.z += 1.0;

	yVec = normal.cross(aux);
	yVec.normalize();

	xVec = yVec.cross(normal);
	xVec.normalize();
}


SpectralQuantity DiskLight::getIntensity(const Vec3 &from)
{
	return intensity*MAX(i.normal.dot(from), 0.0);
}


bool DiskLight::intersect(const Ray& r) {
	const double n_dot_d = i.normal.dot(r.d);
	Vec3 intersection_point;

	if (n_dot_d < 0.0) {
		float distance = (i.normal.dot(centre - r.o)) / n_dot_d;

		if (distance >= 0.0) {
			intersection_point = r.o + r.d * distance;

			float dist = (intersection_point - centre).length();
			if(dist <= radius){
				this->i.dist = distance;
				//A normal já foi definida no construtor
				this->i.point = intersection_point;
				this->i.point += this->i.normal * 0.0001;

				return true;
			}
		}
	}

	return false;
}


Vec3 DiskLight::samplePoint(){
	float phi = 2.0*M_PI*RAND(0.0, 1.0);
	float r = radius*sqrt(RAND(0.0, 1.0));

	Vec3 point = centre + xVec*r*cos(phi) + yVec*r*sin(phi);
	return point + i.normal*0.0001;
}


void DiskLight::getNormal(Vec3 point, Vec3 &norm){
	norm = i.normal;
}


SpectralQuantity DiskLight::computeLocalShading(const Intersection& intersection,
												const SpectralQuantity& intensity,
												const Vec3& toLight,
												const Vec3& toView)
{
	//FIXME: É só isso mesmo? Não tem que multiplicar por algum fator cossenoidal?
	return this->intensity;
}
