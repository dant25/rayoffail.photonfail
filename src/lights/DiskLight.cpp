
#include "DiskLight.h"

DiskLight::DiskLight(	const SpectralQuantity &intensity,
						const Vec3 &centre,
						const Vec3 &normal,
						float radius)
:	Light(intensity),
 	centre(centre),
 	radius(radius)
{
	i.normal = normal;
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
	//TODO: Implementar
	return Vec3();
}


void DiskLight::getNormal(Vec3 point, Vec3 &norm){
	norm = i.normal;
}


SpectralQuantity DiskLight::computeLocalShading(const Intersection& lIntersect, const SpectralQuantity& intensity, const Vec3& rayOrigin)
{
	//FIXME: É só isso mesmo? Não tem que multiplicar por algum fator cossenoidal?
	return this->intensity;
}
