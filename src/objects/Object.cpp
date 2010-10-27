#include "Object.h"
#include <cmath>
#include "../math/Utilities.h"


Object::Object(const Material& mat) : m(mat){
}


SpectralQuantity Object::computeLocalShading(const Intersection& intersection,
                                     const SpectralQuantity& intensity,
                                     const Vec3& toLight,
                                     const Vec3& toView)
{
	   SpectralQuantity color;
	   SpectralQuantity mkd;
	   if(this->m.tex)
	      mkd = this->m.tex->getColor(intersection.texCoord[0], intersection.texCoord[1]);
	   else
	      mkd = this->m.kd;

	   SpectralQuantity diff = mkd*intensity*MAX(dot(intersection.normal, toLight), 0.0);

	   Vec3 reflected = toLight.getReflected(intersection.normal);
	   SpectralQuantity spec = this->m.ks*intensity*pow(MAX(dot(toView, reflected), 0.0), this->m.shininess);

	   color = diff + spec;
	   return color;
}
