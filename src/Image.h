#ifndef IMAGE_H_
#define IMAGE_H_


#include "SpectralQuantity.h"

class Image {
public:
    Image(int width, int height);
    ~Image();
    void save(const char* path);
    
    void setPixel(int x, int y, const SpectralQuantity& c);

    int getWidth() const;
    int getHeight() const;
private:
    int width, height;
    SpectralQuantity **color;
};

#endif
