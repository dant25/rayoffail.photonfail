#include "Sphere.h"
#include <cmath>

Sphere::Sphere(float radius, Vec3 center) : radius(radius), c(center) {
}

bool Sphere::intersect(const Ray& r) {
   //Assume que r.d está normalizado
   //a, b, e c são os coeficientes da equação do segundo grau
   float a = dot(r.d, r.d);
   float b = (dot(r.d, r.o - this->c))*2.0;
   float c = dot(r.o - this->c, r.o - this->c) - radius*radius;

   float delta = b*b - 4*a*c;

   if(delta < 0.0)
      return false;
   else if (delta == 0){
      float dist = -b/2.0*a;
      if(dist > 0) {
         this->i.dist = dist;
         this->i.point = r.o + r.d*dist;
         this->i.normal = (this->i.point - this->c)/radius;
         return true;
      } else
         return false;
   } else {
      float sqrtDelta = sqrtf(delta);
      float t0 = (-b - sqrtDelta)/(2*a);
      float t1 = (-b + sqrtDelta)/(2*a);

      float smallest = (t0 < t1) ? t0 : t1;
      float largest = (t0 > t1) ? t0 : t1;
      
      float dist;
      if(smallest < 0) 
         dist = largest;
      else 
         dist = smallest;

      if(dist < 0) 
         return false;
      else {
         this->i.dist = dist;
         this->i.point = r.o + r.d*dist;
         //FIXME inverter normal se dist == largest?
         this->i.normal = (this->i.point - this->c)/radius;
         return true;
      }
   }
}

SpectralQuantity Sphere::computeLocalShading(const Intersection& lIntersect,
      const SpectralQuantity& diffuse,
      const SpectralQuantity& specular,
      const SpectralQuantity& ambient) const {
   return SpectralQuantity(1.0, 0.0, 0.0);
}
