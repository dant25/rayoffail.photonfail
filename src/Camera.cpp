
#include <iostream>
#include <cstdlib>
#include "math/Utilities.h"
#include "Camera.h"


using namespace std;


Camera::Camera(const Vec3 &pos, const Vec3 &lookat, const Vec3 &up, int x_res, int y_res, float focal_dist)
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

    dof = false;
}


void Camera::depthOfField(bool dof_)
{
	dof = dof_;
}


void Camera::setDepthOfField(float focalPlaneDist_, float lensRadius_)
{
	focalPlaneDist = focalPlaneDist_;
	lensRadius = lensRadius_;
}


Ray Camera::generateRay(int x, int y) const {

    float _W = W-dp;
    float _H = H-dp;

    Vec3 dir;

	if(dof)
	{
    	Vec3 lens_centre = position;

    	Vec3 film_centre = lens_centre + lookat*(-focal_dist);
    	Vec3 film_point = film_centre + (up*((_H/2.0)-(y*dp)+RAND(-dp/2.0, dp/2.0))) + (right*((x*dp)-(_W/2.0)+RAND(-dp/2.0, dp/2.0)));
        float h = (film_point - film_centre).length();
        float D = focalPlaneDist*sqrt(1.0 + ((h*h)/(focal_dist*focal_dist)));
        Vec3 Q = (lens_centre - film_point);
        Q.normalize();
        Q = lens_centre + Q*D;

    	float phi = 2.0*M_PI*RAND(0.0, 1.0);
    	float r = lensRadius*sqrt(RAND(0.0, 1.0));
        Vec3 lens_point = lens_centre + right*r*cos(phi) + up*r*sin(phi);
        dir = (Q - lens_point);
        dir.normalize();

        return Ray(lens_point, dir);
	}
	else
	{
		/*
		//Na direção do meio do pixel
		Vec3 dir = (lookat*focal_dist) + (up*((_H/2.0)-(y*dp))) + (right*((x*dp)-(_W/2.0)));
		dir.normalize();
		*/

		//Direçao aleatória passando pelo pixel
		/*Vec3*/ dir = (lookat*focal_dist) + (up*((_H/2.0)-(y*dp)+RAND(-dp/2.0, dp/2.0))) + (right*((x*dp)-(_W/2.0)+RAND(-dp/2.0, dp/2.0)));
		dir.normalize();
	}

	return Ray(position, dir);
}
