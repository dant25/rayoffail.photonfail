#include "Camera.h"

Camera::Camera(int xres, int yres, const Vec3& pos, const Vec3& lookat, const Vec3& up) 
    : imgWidth(xres), imgHeight(yres), pos(pos), lookat(lookat), up(up){
}

Ray Camera::generateRay(int x, int y) const {
   float xw = 2*this->pos.z*(x - imgWidth/2.0)/imgWidth;
   float yw = 2*this->pos.z*(y - imgHeight/2.0)/imgHeight;
   
   Vec3 p = this->pos + Vec3(xw, yw, -pos.z);

   Vec3 dir = normalize(p - this->pos);
   Ray r;
   r.o = pos;
   r.d = dir;
   return r;
}

int Camera::getWidth() const {
    return imgWidth;
}

int Camera::getHeight() const {
    return imgHeight;
}
