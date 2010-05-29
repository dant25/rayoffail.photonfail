#ifndef OBJECT_H_
#define OBJECT_H_

#include "../math/Ray.h"
#include "../math/Intersection.h"
#include "../SpectralQuantity.h"
#include "../Material.h"
#include "../Transform.h"

typedef struct BBox_{
	float minx, miny, minz;
	float maxx, maxy, maxz;
} BBox;

class Object {
public:
    Object(const Material& mat);

    virtual bool intersect(const Ray& r) = 0;
    virtual Vec3 samplePoint() = 0;
    virtual void getNormal(Vec3 point, Vec3 &normal) = 0;

    virtual SpectralQuantity computeLocalShading(const Intersection& lIntersect,
                                         const SpectralQuantity& intensity,
                                         const Vec3& rayOrigin);
    Intersection getIntersection();


    float getSpecularity(){
    	return m.spec;
    }

   Transform t;
protected:
    //Armazena o último ponto de interseção
    Intersection i;
    Material m;
};

#endif
