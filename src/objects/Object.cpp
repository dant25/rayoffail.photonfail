#include "Object.h"
#include <cmath>
#include "../math/Utilities.h"


Object::Object(const Material& mat) : m(mat){
}


Intersection Object::getIntersection() {
   return i;
}

SpectralQuantity Object::computeLocalShading(const Intersection& lIntersect,
                                             const SpectralQuantity& intensity,
                                             const Vec3 &cameraPos) {
   SpectralQuantity color;
   SpectralQuantity mkd;
   if(this->m.tex) 
      mkd = this->m.tex->getColor(i.texCoord[0], i.texCoord[1]);
   else
      mkd = this->m.kd;

   Vec3 lightVec = lIntersect.point - this->i.point;
   float lightDist = 1.0;//lightVec.length();
   lightVec.normalize();

   SpectralQuantity diff = mkd*intensity*MAX(dot(this->i.normal, lightVec), 0.0)/(lightDist*lightDist);

   Vec3 viewVec = normalize(cameraPos - this->i.point);
   Vec3 reflected = lightVec.getReflected(this->i.normal);
   SpectralQuantity spec = this->m.ks*intensity*pow(MAX(dot(viewVec, reflected), 0.0), this->m.shininess);
   
   color = diff + spec;
   return color;
}
