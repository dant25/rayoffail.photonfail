#include "SpectralQuantity.h"

SpectralQuantity::SpectralQuantity(float r, float g, float b) {
    data[0] = r;
    data[1] = g;
    data[2] = b;
}

SpectralQuantity SpectralQuantity::operator+(const SpectralQuantity& s) const {
   //SpectralQuantity result;
    //result.data[0] = this->data[0] + s.data[0] > 1.0 ? 1.0 : this->data[0] + s.data[0];
    //result.data[1] = this->data[1] + s.data[1] > 1.0 ? 1.0 : this->data[1] + s.data[1];
    //result.data[2] = this->data[2] + s.data[2] > 1.0 ? 1.0 : this->data[2] + s.data[2];
    //return result; 
    return SpectralQuantity(this->data[0] + s.data[0], this->data[1] + s.data[1],
                           this->data[2] + s.data[2]);  
}
SpectralQuantity SpectralQuantity::operator*(const SpectralQuantity& s) const {
   //SpectralQuantity result;
    //result.data[0] = this->data[0]*s.data[0] > 1.0 ? 1.0 : this->data[0]*s.data[0];
    //result.data[1] = this->data[1]*s.data[1] > 1.0 ? 1.0 : this->data[1]*s.data[1];
    //result.data[2] = this->data[2]*s.data[2] > 1.0 ? 1.0 : this->data[2]*s.data[2];
    //return result;
   return SpectralQuantity(this->data[0]*s.data[0], this->data[1]*s.data[1],
                           this->data[2]*s.data[2]);
}

SpectralQuantity SpectralQuantity::operator*(float s) const {
    //SpectralQuantity result;
    //result.data[0] = this->data[0]*s > 1.0 ? 1.0 : this->data[0]*s;
    //result.data[1] = this->data[1]*s > 1.0 ? 1.0 : this->data[1]*s;
    //result.data[2] = this->data[2]*s > 1.0 ? 1.0 : this->data[2]*s;
    //return result;
   return SpectralQuantity(this->data[0]*s, this->data[1]*s, this->data[2]*s);
}
