#include "Camera.h"

Camera::Camera(int xres, int yres, const Vec3& pos, const Vec3& lookat, const Vec3& up) 
    : imgWidth(xres), imgHeight(yres), pos(pos), lookat(lookat), up(up){
}

Ray Camera::generateRay(int x, int y) const {
    Ray r;
    r.origin = this->pos;

    //Raio ortogonal mazela
    r.dir = Vec3(0.0, 0.0, -1.0);

    return r;
}

int Camera::getWidth() const {
    return imgWidth;
}

int Camera::getHeight() const {
    return imgHeight;
}
