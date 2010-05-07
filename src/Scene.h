#ifndef SCENE_H_
#define SCENE_H_

#include "SpectralQuantity.h"
#include "Container.h"
#include "../math/Ray.h"

class Scene {
public:
    SpectralQuantity render(const Ray& r) const;
    //addObj
    //addLight
    
private:
    Container objects;
};

#endif

