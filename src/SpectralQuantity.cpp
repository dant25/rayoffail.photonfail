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

SpectralQuantity SpectralQuantity::operator*(float s) const {
   return SpectralQuantity(this->data[0]*s, this->data[1]*s, this->data[2]*s);
}

SpectralQuantity& SpectralQuantity::operator+=(const SpectralQuantity& s) {
   this->data[0] += s.data[0];
   this->data[1] += s.data[1];
   this->data[2] += s.data[2];
   return *this;
}

SpectralQuantity SpectralQuantity::operator/(float s) const {
   return SpectralQuantity(this->data[0]/s, this->data[1]/s, this->data[2]/s);
}


SpectralQuantity& SpectralQuantity::operator/=(float s) {
    this->data[0] /= s;
    this->data[1] /= s;
    this->data[2] /= s;

    return *this;
}


SpectralQuantity SpectralQuantity::operator*=(const SpectralQuantity& s) {
    this->data[0] *= s.data[0];
    this->data[1] *= s.data[1];
    this->data[2] *= s.data[2];

    return *this;
}
