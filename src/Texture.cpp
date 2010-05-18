#include "Texture.h"

Texture::Texture(const char* path) {
   img.load(path);
}

SpectralQuantity Texture::getColor(float u, float v) {
   int imgX = int(u*img.getWidth());
   int imgY = int(v*img.getHeight());
   
   //FIXME usar algum tipo de interpolação
   return img.getPixel(imgX, imgY);
}
