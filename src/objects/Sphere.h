#ifndef SPEHERE_H_
#define SPEHERE_H_

#include "Object.h"

class Sphere : public Object {
public:
    Sphere(const Material& mat, float radius, Vec3 center);

    //Implementação da interface de Object
    virtual bool intersect(const Ray& r);
    virtual bool shadowintersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

private:
    float radius;
    Vec3 centre;
};

#endif
