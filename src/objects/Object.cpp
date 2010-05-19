#include "Object.h"
#include <cmath>

Object::Object(const Material& mat) : m(mat){
}

Intersection Object::getIntersection() {
   return i;
}


//FIXME: função placeholder
float max(float x, float y) {
   return x > y ? x : y;
}

SpectralQuantity Object::computeLocalShading(const Intersection& lIntersect,
                                             const SpectralQuantity& intensity,
                                             const Vec3 &cameraPos) {
   SpectralQuantity color;

   Vec3 lightVec = normalize(lIntersect.point - this->i.point);
   SpectralQuantity diff = this->m.kd*intensity*max(dot(this->i.normal, lightVec), 0.0);

   Vec3 viewVec = normalize(cameraPos - this->i.point);
   Vec3 reflected = lightVec.getReflected(this->i.normal);
   SpectralQuantity spec = this->m.ks*intensity*pow(max(dot(this->i.normal, reflected), 0.0), this->m.shininess);
   
   color = diff + spec;
   return color;
}
