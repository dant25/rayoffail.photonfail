#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Image.h"
#include "SpectralQuantity.h"

class Texture {
   public:
      Texture(const char* path);

      SpectralQuantity getColor(float u, float v);
   private:
      Image img;
};

#endif
