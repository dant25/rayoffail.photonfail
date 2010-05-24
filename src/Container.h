#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "objects/Object.h"
#include "math/Ray.h"

#include <vector>

class Container {
public:
   void addObject(Object *obj);
   Object* findObject(const Ray& r) const;
   Object* findShadowObject(const Ray& r) const;
//private:
    //TODO: Estrutura de dados pra armazenar objetos.
    std::vector<Object*> objects;
};

#endif
