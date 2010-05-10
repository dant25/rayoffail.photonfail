#include "SpectralQuantity.h"

SpectralQuantity::SpectralQuantity(float r, float g, float b) {
    data[0] = r;
    data[1] = g;
    data[2] = b;
}

SpectralQuantity SpectralQuantity::operator+(const SpectralQuantity& s) const {
   return SpectralQuantity(this->data[0] + s.data[0], this->data[1] + s.data[1],
                           this->data[2] + s.data[2]);
}
SpectralQuantity SpectralQuantity::operator*(const SpectralQuantity& s) const {
   return SpectralQuantity(this->data[0]*s.data[0], this->data[1]*s.data[1],
                           this->data[2]*s.data[2]);
}
