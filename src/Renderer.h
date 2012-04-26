#ifndef RENDERER_H_
#define RENDERER_H_

#include "Scene.h"
#include "Camera.h"
#include "Image.h"

class Renderer {
public:
    Image* render(const Scene& s, const Camera& c);
};

#endif

