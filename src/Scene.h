#ifndef SCENE_H_
#define SCENE_H_

#include "SpectralQuantity.h"
#include "Container.h"
#include "../math/Ray.h"
#include "Light.h"
#include <vector>

class Scene {
public:
    SpectralQuantity render(const Ray& r) const;
    void addObject(Object* obj);
    void addLight(Light*  l);
    
private:
    Container objects;
    std::vector<Light*> lights;
};

#endif

