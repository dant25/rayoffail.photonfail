
#include <iostream>
#include <cstdlib>
#include "math/Utilities.h"
#include "Camera.h"


using namespace std;

#define RAND(inf, sup) (inf + ((((sup)-(inf))/(float)RAND_MAX)*rand()))
#define PROB(prob) (rand() < ((prob)*(RAND_MAX-1)))
#define MAX(x, y) ((x)<(y)?(y):(x))


Camera::Camera(const Vec3 &pos, const Vec3 &lookat, const Vec3 &up, int x_res, int y_res, float focal_dist, int num_samples)
:   L(1.0)
{
    this->position = pos;
    this->lookat = lookat;
    this->up = up;
    this->x_res = x_res;
    this->y_res = y_res;
    this->focal_dist = focal_dist;
    right = lookat.cross(up);

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

    this->num_samples = num_samples;
}


Ray Camera::generateRay(int x, int y) const {
	/*
    float _W = W-dp;
    float _H = H-dp;

    Vec3 dir = (lookat*focal_dist) + (up*((_H/2.0)-(y*dp))) + (right*((x*dp)-(_W/2.0)));
    dir.normalize();

    return Ray(position, dir);
    */

    float _W = W-dp;
    float _H = H-dp;

    Vec3 delta_up = up*RAND(-dp, dp);
    Vec3 delta_right = right*RAND(-dp, dp);

    Vec3 dir = (lookat*focal_dist) + (up*((_H/2.0)-(y*dp)+RAND(-dp/2.0, dp/2.0))) + (right*((x*dp)-(_W/2.0)+RAND(-dp/2.0, dp/2.0)));
    dir.normalize();

    return Ray(position, dir);
}


