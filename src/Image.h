#ifndef IMAGE_H_
#define IMAGE_H_

#include "SpectralQuantity.h"

class Image {
   public:
      Image();
      Image(int width, int height);
      ~Image();

      void save(const char* path);
      void load(const char* path);

      void setPixel(int x, int y, const SpectralQuantity& c);
      SpectralQuantity getPixel(int x, int y) const;

      int getWidth() const;
      int getHeight() const;

private:
      void clear();

      int width, height;
      SpectralQuantity **color;
};

#endif
