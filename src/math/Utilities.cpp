#include "Utilities.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void barycentricCoords(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p,
                       float &l1, float &l2, float &l3) {
//   float detT = (p1.x - p3.x)*(p2.y - p3.y) - ((p1.y - p3.y)*(p2.x - p3.x));
//   l1 = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y))/detT;
//   l2 = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y))/detT;
//   l3 = 1.0 - l1 - l2;
   float area = cross(p2 - p1, p3 - p1).length();
   l1 = cross(p1 - p, p2 - p).length()/area;
   l2 = cross(p2 - p, p3 - p).length()/area;
//   l3 = cross(p2 - p1, p - p1).length()/area;
   l3 = 1.0 - l1 - l2;
}


float strToFloat(const char *str)
{
	float val;
	std::string string(str);
 	std::stringstream stream;
	stream << string;
	stream >> val;

	return val;
}

Vec3 UniformSampleHemisphere(float u1, float u2) {
    float z = u1;
    float r = sqrtf(max(0.f, 1.f - z*z));
    float phi = 2 * M_PI * u2;
    float x = r * cosf(phi);
    float y = r * sinf(phi);
    return Vec3(x, y, z);
}

void ConcentricSampleDisk(float u1, float u2, float *dx, float *dy) {
    float r, theta;
    // Map uniform random numbers to $[-1,1]^2$
    float sx = 2 * u1 - 1;
    float sy = 2 * u2 - 1;
    // Map square to $(r,\theta)$
    // Handle degeneracy at the origin
    if (sx == 0.0 && sy == 0.0) {
        *dx = 0.0;
        *dy = 0.0;
        return;
    }
    if (sx >= -sy) {
        if (sx > sy) {
            // Handle first region of disk
            r = sx;
            if (sy > 0.0) theta = sy/r;
            else          theta = 8.0f + sy/r;
        }
        else {
            // Handle second region of disk
            r = sy;
            theta = 2.0f - sx/r;
        }
    }
    else {
        if (sx <= sy) {
            // Handle third region of disk
            r = -sx;
            theta = 4.0f - sy/r;
        }
        else {
            // Handle fourth region of disk
            r = -sy;
            theta = 6.0f + sx/r;
        }
    }
    theta *= M_PI / 4.f;
    *dx = r * cosf(theta);
    *dy = r * sinf(theta);
}
//Amostra com maior probabilidade na direção da normal
Vec3 CosineSampleHemisphere(float u1, float u2, Vec3 n) {
    Vec3 ret;
    ConcentricSampleDisk(u1, u2, &ret.x, &ret.y);
    ret.z = sqrtf(max(0.f, 1.f - ret.x*ret.x - ret.y*ret.y));

    Vec3 dpdu(-ret.y, ret.x, 0.f);

    Vec3 nn = n;
    Vec3 sn = normalize(dpdu);
    Vec3 tn = cross(nn, sn);
    
    //Local to world
    return Vec3(tn.x*ret.x + sn.x*ret.y + nn.x*ret.z,
                tn.y*ret.x + sn.y*ret.y + nn.y*ret.z,
                tn.z*ret.x + sn.z*ret.y + nn.z*ret.z);
}
