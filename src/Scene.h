#ifndef SCENE_H_
#define SCENE_H_

#include "SpectralQuantity.h"
#include "Container.h"
#include "math/Ray.h"
#include "lights/Light.h"
#include <vector>
#include <map>
#include <string>

class Scene {
public:
	Scene();

    SpectralQuantity render(const Ray& r) const;
    void addObject(Object* obj);
    void addLight(Light*  l);
    void addMaterial(const char *label, Material *m);
   
    Material* getMaterial(const char *label);
//private:
    Container objects;
    std::vector<Light*> lights;
    std::map<std::string, Material*> materials;

    SpectralQuantity ambient_color;
    SpectralQuantity background_color;
    int maxDepth;

    SpectralQuantity render(const Ray& r, int depth) const;
};

#endif

