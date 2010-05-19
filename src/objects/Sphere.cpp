#include "Sphere.h"

#include "../math/Utilities.h"
#include <cmath>

Sphere::Sphere(const Material& mat, float radius, Vec3 center) : Object(mat), radius(radius), centre(center) {
}


bool Sphere::intersect(const Ray& r) {
   //Assume que r.d está normalizado
   //a, b, e c são os coeficientes da equação do segundo grau
   float a = dot(r.d, r.d);
   float b = (dot(r.d, r.o - this->centre))*2.0;
   float c = dot(r.o - this->centre, r.o - this->centre) - radius*radius;

   float delta = b*b - 4*a*c;

   if(delta < 0.0)
      return false;
   else if (delta == 0){
      float dist = -b/2.0*a;
      if(dist > 0) {
         this->i.dist = dist;
         this->i.point = r.o + r.d*dist;
         this->i.normal = (this->i.point - this->centre)/radius;
         this->i.point += this->i.normal*0.0001;
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
         this->i.normal = (this->i.point - this->centre)/radius;
         this->i.point += this->i.normal*0.0001;
         return true;
      }
   }
}


Vec3 Sphere::samplePoint(){
	float rand1 = RAND(0.0, 1.0);
	float rand2 = RAND(0.0, 1.0);

	Vec3 point(
		centre.x + 2.0*radius*cos(2.0*M_PI*rand2)*sqrt(rand1*(1.0 - rand1)),
		centre.y + 2.0*radius*sin(2.0*M_PI*rand2)*sqrt(rand1*(1.0 - rand1)),
		centre.z + radius*(1.0 - 2.0*rand1)
	);

	Vec3 normal = point - centre;
	normal.normalize();

	return point + normal*0.0001;
}


void Sphere::getNormal(Vec3 point, Vec3 &normal){
	normal = point - centre;
	normal.normalize();
}
