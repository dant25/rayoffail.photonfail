#include "Renderer.h"

#include <iostream>

Image*  Renderer::render(const Scene& s, const Camera& c) {
    Image *img = new Image(c.getWidth(), c.getHeight());
//    int numSamples = 32;

    //Loop principal, cria numSamples raios pra cada pixel
    SpectralQuantity color;
    for(int i = 0; i < img->getWidth(); i++){
        for(int j = 0; j < img->getHeight(); j++) {
			Ray r = c.generateRay(i, j);
			img->setPixel(i, j, img->getPixel(i, j) + s.render(r));
        }
    }

    return img;
}
