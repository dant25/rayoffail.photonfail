#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "math/Mat4x4.h"
#include "math/Vec3.h"
#include "math/Ray.h"

class Transform {
    public:
        Transform();
        Transform(Mat4x4 m, Mat4x4 mInv);
        Transform getInverse();
        
        Vec3 operator*(const Vec3& v);
        Ray operator*(const Ray& r);
        Vec3 transformNormal(const Vec3& normal);

        //TODO URGENTE concatenar transformações!

        Mat4x4 mat;
        Mat4x4 invMat;
};

Transform translate(const Vec3& delta);
Transform rotateX(float angle);
Transform rotateY(float angle);
Transform rotateZ(float angle);

#endif
