#include "Container.h"
#include <cmath>

#include <iostream>

//TODO: usar estrutura de dados melhor

void Container::addObject(Object *obj) {
    objects.push_back(obj);
}

Object* Container::findObject(const Ray& r, Intersection &intersection) const {
    Object *obj = NULL;

    float dist = INFINITY;
    for(unsigned int i = 0; i < objects.size(); i++) {
        Intersection temp_intersect;
        if(objects[i]->intersect(r, temp_intersect)) {
            //Aponta para o novo objeto se a distância for a menor encontrada até
            //o momento
            if(dist > temp_intersect.dist) {
                obj = objects[i];
                dist = temp_intersect.dist;
                intersection = temp_intersect;
            }
        }
    }

    return obj;
}
