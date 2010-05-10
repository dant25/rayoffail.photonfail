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
                                             const SpectralQuantity& diffuse,
                                             const SpectralQuantity& specular,
                                             const SpectralQuantity& ambient,
                                             const Vec3 &cameraPos) {
   SpectralQuantity color;
   SpectralQuantity amb = this->m.ka*ambient;

   Vec3 lightVec = normalize(lIntersect.point - this->i.point);
   SpectralQuantity diff = this->m.kd*diffuse*max(dot(this->i.normal, lightVec), 0.0);

   Vec3 viewVec = normalize(cameraPos - this->i.point);
   Vec3 halfVec = normalize(lightVec + viewVec);
   SpectralQuantity spec = this->m.ks*specular*pow(max(dot(this->i.normal, halfVec), 0.0), this->m.shininess);
   
   color = amb + diff + spec;
   return color;
}
