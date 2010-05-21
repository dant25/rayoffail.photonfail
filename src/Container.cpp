#include "Container.h"
#include <cmath>

#include <iostream>

//TODO: usar estrutura de dados melhor

void Container::addObject(Object *obj) {
   objects.push_back(obj);
}

Object* Container::findObject(const Ray& r) const {
   Object *obj = NULL;

   float dist = INFINITY;
   for(int i = 0; i < objects.size(); i++) {
      if(objects[i]->intersect(r)) {
         //Aponta para o novo objeto se a distância for a menor encontrada até
         //o momento
         if(dist > objects[i]->getIntersection().dist) {
            obj = objects[i];
            dist = obj->getIntersection().dist;
         }
      }
   }

   return obj;
}
