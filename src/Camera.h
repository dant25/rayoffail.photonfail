#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vec3.h"
#include "math/Ray.h"

class Camera{
public:
    Camera(const Vec3 &pos, const Vec3 &lookat, const Vec3 &up, int x_res = 500, int y_res = 500, float focal_dist = 1.0);

    Ray generateRay(int x, int y) const;

    void depthOfField(bool);
    void setDepthOfField(float focalPlaneDist, float lensRadius);

    int getWidth() const {
    	return x_res;
    }

    int getHeight() const {
    	return y_res;
    }

    void setResolution(int x, int y){
    	x_res = x;
    	y_res = y;

        if(x_res > y_res){
            dp = L/(float)x_res;
            H = dp*y_res;
            W = L;
        }
        else{
            dp = L/y_res;
            W = dp*x_res;
            H = L;
        }
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

    const float L;

    //Parâmetros de profundidade de campo
    bool dof;				// Liga ou desliga.
    float focalPlaneDist;	// Distancia entre o plano de focagem perfeita e a lente.
    float lensRadius;			// Raio da lente.
};

#endif
