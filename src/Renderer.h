#ifndef RENDERER_H_
#define RENDERER_H_

#include "Scene.h"
#include "Camera.h"
#include "Image.h"

class Renderer {
public:
    Image* render(const Scene& s, const Camera& c, int minw = 0, int incrw = 1, int maxw = -1, int minh = 0, int incrh = 1, int maxh = -1);
};

#endif

