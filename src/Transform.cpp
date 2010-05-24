#include "Transform.h"
#include <cmath>

Transform::Transform() {
    mat.loadIdentity();
    invMat.loadIdentity();
}

Transform::Transform(Mat4x4 m, Mat4x4 mInv) : mat(m), invMat(mInv) {
}

Transform Transform::getInverse() {
    return Transform(invMat, mat);
}

Vec3 Transform::operator*(const Vec3& v) {
    Vec3 result;
    result.x = mat(0, 0)*v.x + mat(0, 1)*v.y + mat(0, 2)*v.z + mat(0, 3)*v.w;
    result.y = mat(1, 0)*v.x + mat(1, 1)*v.y + mat(1, 2)*v.z + mat(1, 3)*v.w;
    result.z = mat(2, 0)*v.x + mat(2, 1)*v.y + mat(2, 2)*v.z + mat(2, 3)*v.w;
    
    result.w = v.w;
    //FIXME considerar componente w pra o ponto?
    //w =  mat(3, 0)*v.x + mat(3, 1)*v.y + mat(3, 2)*v.z + mat(3, 3);

    return result;
}

Ray Transform::operator*(const Ray& r) {
    Ray result;

    result.o = (*this)*(r.o);
    result.d = (*this)*(r.d);

    return result;
}

Vec3 Transform::transformNormal(const Vec3& normal) {
    Vec3 result;

    result.x = mat(0, 0)*normal.x + mat(1, 0)*normal.y + mat(2, 0)*normal.z;
    result.y = mat(0, 1)*normal.x + mat(1, 1)*normal.y + mat(2, 1)*normal.z;
    result.z = mat(0, 2)*normal.x + mat(1, 2)*normal.y + mat(2, 2)*normal.z;
    return result;
}

Transform translate(const Vec3& delta) {
    Mat4x4 m, mInv;
    //m e mInv são a identidade, logo só os elementos
    //da última coluna precisam mudar
    m(0, 3) = delta.x;
    m(1, 3) = delta.y;
    m(2, 3) = delta.z;

    mInv(0, 3) = -delta.x;
    mInv(1, 3) = -delta.y;
    mInv(2, 3) = -delta.z;

    return Transform(m, mInv);
}

Transform rotateX(float angle) {
    Mat4x4 m, mInv;
    //A constante abaixo é igual a PI/180.0
    float angleRadians = angle*0.0174532925;
    float c = cos(angleRadians);
    float s = sin(angleRadians);

    float invC = cos(-angleRadians);
    float invS = sin(-angleRadians);

    m(1, 1) = c;
    m(1, 2) = -s;

    m(2, 1) = s;
    m(2, 2) = c;
    
    mInv(1, 1) = invC;
    mInv(1, 2) = -invS;

    mInv(2, 1) = invS;
    mInv(2, 2) = invC;

    return Transform(m, mInv);
}

Transform rotateY(float angle) {
    Mat4x4 m, mInv;
    //A constante abaixo é igual a PI/180.0
    float angleRadians = angle*0.0174532925;
    float c = cos(angleRadians);
    float s = sin(angleRadians);

    float invC = cos(-angleRadians);
    float invS = sin(-angleRadians);

    m(0, 0) = c;
    m(0, 2) = s;

    m(2, 0) = -s;
    m(2, 2) = c;
    
    mInv(0, 0) = invC;
    mInv(0, 2) = invS;

    mInv(2, 0) = -invS;
    mInv(2, 2) = invC;

    return Transform(m, mInv);
}

Transform rotateZ(float angle) {
    Mat4x4 m, mInv;
    //A constante abaixo é igual a PI/180.0
    float angleRadians = angle*0.0174532925;
    float c = cos(angleRadians);
    float s = sin(angleRadians);

    float invC = cos(-angleRadians);
    float invS = sin(-angleRadians);

    m(0, 0) = c;
    m(0, 1) = -s;

    m(1, 0) = s;
    m(1, 1) = c;
    
    mInv(0, 0) = invC;
    mInv(0, 1) = -invS;

    mInv(1, 0) = invS;
    mInv(1, 1) = invC;

    return Transform(m, mInv);
}
