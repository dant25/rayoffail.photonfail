#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vec3.h"
#include "math/Ray.h"

class Camera{
public:
    Camera(const Vec3 &pos, const Vec3 &lookat, const Vec3 &up, int x_res = 500, int y_res = 500, float focal_dist = 1.0, int num_samples = 1);

    Ray generateRay(int x, int y) const;

    int getWidth() const {
    	return x_res;
    }

    int getHeight() const {
    	return y_res;
    }

private:
    Vec3 position;
    Vec3 lookat;
    Vec3 up;
    Vec3 right;

    int x_res;          // Numero de pixels na horizontal
    int y_res;          // Numero de pixels na vetical
    float focal_dist;
    float dp;           // Tamanho do lado do pixel
    float H;
    float W;

    int num_samples;

    const float L;
};

#endif
