#ifndef CAMERA_H_
#define CAMERA_H_

#include "../math/Ray.h"
#include "../math/Vec3.h"

class Camera {
public:
    Camera(int xres, int yres, const Vec3& pos, const Vec3& lookat, const Vec3& up);
    Ray generateRay(int x, int y) const;

    int getWidth() const;
    int getHeight() const;
    
private:
    int imgWidth, imgHeight;
    Vec3 pos, lookat, up;
};

#endif
