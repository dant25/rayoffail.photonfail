#include "Image.h"
//FIXME escrever a função de ler tga
#include "util/image.h"
#include <stdio.h>

Image::Image() {
   color = NULL;
}

Image::Image(int width, int height) : width(width), height(height) {
    color = new SpectralQuantity*[width];
    for(int i = 0; i < width; i++)
        color[i] = new SpectralQuantity[height];
}

Image::~Image() {
   this->clear();
}

void Image::clear() {
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

double *Image::makeData()
{
	double *data = new double[this->width*this->height*3];

	double *ptr = data;

	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			(*ptr++) = this->color[i][j].data[0];
			(*ptr++) = this->color[i][j].data[1];
			(*ptr++) = this->color[i][j].data[2];
		}
	}

	return data;
}

void Image::setData(double *data)
{
	double *ptr = data;

	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			this->color[i][j].data[0] = (*ptr++);
			this->color[i][j].data[1] = (*ptr++);
			this->color[i][j].data[2] = (*ptr++);
		}
	}
}

void Image::setPixel(int x, int y, const SpectralQuantity& c) {
    color[x][y] = c;

    if(c.data[0] > 1.0)
       color[x][y].data[0] = 1.0;
    if(c.data[1] > 1.0)
       color[x][y].data[1] = 1.0;
    if(c.data[2] > 1.0)
       color[x][y].data[2] = 1.0;
}

SpectralQuantity Image::getPixel(int x, int y) const {
   if(x > width)
      x = width;
   if(y > height)
      y = height;
	return color[x][y];
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

	for (int y = height - 1; y >= 0; y--) {
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

void Image::load(const char* path) {
   if(color)
      clear();
   unsigned char* data = NULL;
   int x, y, n;
   data = stbi_load(path, &x, &y, &n, 0);
   width = x;
   height = y;

   color = new SpectralQuantity*[width];
   for(int i = 0; i < width; i++)
      color[i] = new SpectralQuantity[height];

   for(int j = 0; j < height; j++)
      for(int i = 0; i < width; i++)
         color[i][j] = SpectralQuantity(data[3*j*width + i*3]/255.0,
                                        data[3*j*width + i*3 + 1]/255.0,
                                        data[3*j*width + i*3 + 2]/255.0);

   stbi_image_free(data);
}
