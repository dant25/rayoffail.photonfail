
#include "QuadLight.h"

#include "../math/Utilities.h"
#include <iostream>

using namespace std;

QuadLight::QuadLight(const SpectralQuantity &intensity, const Vec3 &centre, const Vec3 &at_width, const Vec3 &at_height)
:	Light(intensity),
 	centre(centre),
 	at_width(at_width),
 	at_height(at_height)
{
    i.normal = at_height.cross(at_width);
    i.normal.normalize();

    width = at_width.length();
    this->at_width.normalize();

    height = at_height.length();
    this->at_height.normalize();
}


bool QuadLight::intersect(const Ray& r) {
	const double n_dot_d = i.normal.dot(r.d);
	Vec3 intersection_point;

	if (n_dot_d < 0.0) {
		float distance = (i.normal.dot(centre - r.o)) / n_dot_d;

		if (distance >= 0.0) {
			intersection_point = r.o + r.d * distance;

			Vec3 corner = centre + (at_width*(width/-2.0)) + (at_height*(height/-2.0));
			Vec3 point_vec = intersection_point - corner;

			float dist = point_vec.length();
			//FIXME: Este teste está errado. Ainda não sei como testar se o ponto está dentro ou fora
			if(dist <= width*height){
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


Vec3 QuadLight::samplePoint(){
	//TODO: Talvez seja preciso deslocar esse ponto um pouco na direção da normal par evitar auto-interseção.

	Vec3 point = centre + ((at_width*RAND(-width/2.0, width/2.0)) + (at_height*RAND(-height/2.0, height/2.0)));
	return centre + i.normal*0.00001;
}


void QuadLight::getNormal(Vec3 point, Vec3 &norm){
	norm = i.normal;
}


SpectralQuantity QuadLight::computeLocalShading(const Intersection& lIntersect, const SpectralQuantity& intensity, const Vec3& rayOrigin)
{
	//FIXME: É só isso mesmo? Não tem que multiplicar por algum fator cossenoidal?
	return this->intensity;
}
