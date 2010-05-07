#include "Object.h"

Object::Object(const Material& mat) : m(mat){
}

Intersection Object::getIntersection() {
    return i;
}
