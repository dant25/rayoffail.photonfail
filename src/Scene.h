#ifndef SCENE_H_
#define SCENE_H_

#include "SpectralQuantity.h"
#include "Container.h"
#include "math/Ray.h"
#include "lights/Light.h"
#include <vector>

class Scene {
public:
	Scene();

    SpectralQuantity render(const Ray& r) const;
    void addObject(Object* obj);
    void addLight(Light*  l);
    
private:
    Container objects;
    std::vector<Light*> lights;

    SpectralQuantity background_color;
    int maxDepth;

    SpectralQuantity render(const Ray& r, int depth) const;
};

#endif

