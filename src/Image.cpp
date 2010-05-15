#include "Image.h"
#include <stdio.h>

Image::Image(int width, int height) : width(width), height(height) {
    color = new SpectralQuantity*[width];
    for(int i = 0; i < width; i++)
        color[i] = new SpectralQuantity[height];
}

Image::~Image() {
    for(int i = 0; i < width; i++)
        delete []color[i];
    delete []color;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

void Image::setPixel(int x, int y, const SpectralQuantity& c) {
    color[x][y] = c;
}

void WriteByte(FILE *file, unsigned char b) {
    fwrite((void*)&b,sizeof(unsigned char),1,file);
}

int clamp(float value) {
   int newValue = int(255*value);
   
   if(newValue > 255)
      newValue = 255;
   else if (newValue < 0)
      newValue = 0;

   return newValue;
}

void Image::save(const char* path) {
	FILE* file;
	file = fopen(path, "wb");

	WriteByte(file, 0);
	WriteByte(file, 0);
	WriteByte(file, 2); //RGB nao compactado

	WriteByte(file, 0);
	WriteByte(file, 0);
	WriteByte(file, 0);
	WriteByte(file, 0);
	WriteByte(file, 0);

	WriteByte(file, 0); //Origem X
	WriteByte(file, 0);
	WriteByte(file, 0); //Origem Y
	WriteByte(file, 0);

	WriteByte(file, (width & 0x00FF));
	WriteByte(file, (width & 0xFF00) / 256);
	WriteByte(file, (height& 0x00FF));
	WriteByte(file, (height& 0xFF00) / 256);

	WriteByte(file, 24);
	WriteByte(file, 0);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//obs: ordem da cor inversa (b, g, r)
            //FIXME tratando SpectralQuantity como uma cor rgb normal!
			WriteByte(file, clamp(color[x][y].data[2]));
			WriteByte(file, clamp(color[x][y].data[1]));
			WriteByte(file, clamp(color[x][y].data[0]));
		}
	}
	fclose(file);
}
