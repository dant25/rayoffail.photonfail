#include "Renderer.h"

Image*  Renderer::render(const Scene& s, const Camera& c) {
    Image *img = new Image(c.getWidth(), c.getHeight());

    //Loop principal, cria um raio pra cada pixel
    for(int i = 0; i < img->getWidth(); i++)
        for(int j = 0; j < img->getHeight(); j++) {
            Ray r = c.generateRay(i, j);
            img->setPixel(i, j, s.render(r));
        }
    return img;
}
