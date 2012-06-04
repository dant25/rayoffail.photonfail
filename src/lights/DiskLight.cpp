
#include "DiskLight.h"

#include <cmath>
#include "../math/Utilities.h"
#include <algorithm>

using namespace std;


DiskLight::DiskLight(	const SpectralQuantity &intensity,
						const Vec3 &centre,
						const Vec3 &normal,
						float radius)
:	Light(intensity),
 	centre(centre),
 	radius(radius)
{
	i.normal = normal;

	// Obtem uma sistema de coordenadas com z = normal
	// FIXME: Tem um jeito melhor de fazer isso?
	Vec3 aux = i.normal;
	aux.x += 1.0;
	aux.y += 1.0;
	aux.z += 1.0;

	yVec = normal.cross(aux);
	yVec.normalize();

	xVec = yVec.cross(normal);
	xVec.normalize();
}


SpectralQuantity DiskLight::getIntensity(const Vec3 &from)
{
	return intensity*MAX(i.normal.dot(from), 0.0);
}


bool DiskLight::intersect(const Ray& r) {
	const double n_dot_d = i.normal.dot(r.d);
	Vec3 intersection_point;

	if (n_dot_d < 0.0) {
		float distance = (i.normal.dot(centre - r.o)) / n_dot_d;

		if (distance >= 0.0) {
			intersection_point = r.o + r.d * distance;

			float dist = (intersection_point - centre).length();
			if(dist <= radius){
				this->i.dist = distance;
				//A normal já foi definida no construtor
				this->i.point = intersection_point;
				this->i.point += this->i.normal * 0.0001;

				return true;
			}
		}
	}

	return false;
}

void CoordinateSystem(const Vec3 &v1, Vec3 *v2, Vec3 *v3) {
    if (fabsf(v1.x) > fabsf(v1.y)) {
        float invLen = 1.f / sqrtf(v1.x*v1.x + v1.z*v1.z);
        *v2 = Vec3(-v1.z * invLen, 0.f, v1.x * invLen);
    }
    else {
        float invLen = 1.f / sqrtf(v1.y*v1.y + v1.z*v1.z);
        *v2 = Vec3(0.f, v1.z * invLen, -v1.y * invLen);
    }
    *v3 = cross(v1, *v2);
}

Vec3 DiskLight::samplePoint(){
    /*float px, py;
    ConcentricSampleDisk(drand48(), drand48(), &px, &py);
    
    Vec3 tempPos(px*radius, py*radius, 0.f);
    Vec3 sn, tn;
    Vec3 nn = i.normal;
    CoordinateSystem(nn, &sn, &tn);
    //Local to world
    Vec3 newpos(tn.x*tempPos.x + sn.x*tempPos.y + nn.x*tempPos.z + centre.x,
                tn.y*tempPos.x + sn.y*tempPos.y + nn.y*tempPos.z + centre.y,
                tn.z*tempPos.x + sn.z*tempPos.y + nn.z*tempPos.z + centre.z);
    return newpos + i.normal*0.0001;*/
	float phi = 2.0*M_PI*drand48();
	float r = radius*sqrt(drand48());

	Vec3 point = centre + xVec*r*cos(phi) + yVec*r*sin(phi);
	return point + i.normal*0.0001;
}


void DiskLight::getNormal(Vec3, Vec3 &norm){
	norm = i.normal;
}


SpectralQuantity DiskLight::computeLocalShading(const Intersection&,
												const SpectralQuantity&,
												const Vec3&,
												const Vec3&)
{
	//FIXME: É só isso mesmo? Não tem que multiplicar por algum fator cossenoidal?
	return this->intensity;
}


//Amostra na direção da normal
/*void DiskLight::SampleDirAndPos(Vec3 *dir, Vec3 *pos) {
    //Amostra um ponto no disco
    float px, py;
    ConcentricSampleDisk(drand48(), drand48(), &px, &py);

    Vec3 tempPos(px, py, 0.f);
    Vec3 dpdu(-py, px, 0.f);

    Vec3 nn = i.normal;
    Vec3 sn = normalize(dpdu);
    Vec3 tn = cross(nn, sn);
    
    Vec3 tempDir(px, py, 0.f);
    tempDir.z = sqrtf(max(0.f, 1.f - tempDir.x*tempDir.x - tempDir.y*tempDir.y));

    //Local to world
    Vec3 newdir(sn.x*tempDir.x + tn.x*tempDir.y + nn.x*tempDir.z,
                sn.y*tempDir.x + tn.y*tempDir.y + nn.y*tempDir.z,
                sn.z*tempDir.x + tn.z*tempDir.y + nn.z*tempDir.z);
    
    Vec3 newpos(sn.x*tempPos.x + tn.x*tempPos.y + nn.x*tempPos.z,
                sn.y*tempPos.x + tn.y*tempPos.y + nn.y*tempPos.z,
                sn.z*tempPos.x + tn.z*tempPos.y + nn.z*tempPos.z);
    newpos = newpos*radius + centre + i.normal*0.0001;
}*/

Vec3 DiskLight::sampleDir() {
    //Amostra um ponto no disco
    /*float px, py;
    ConcentricSampleDisk(drand48(), drand48(), &px, &py);

    Vec3 tempPos(px, py, 0.f);
    Vec3 dpdu(-py, px, 0.f);

    Vec3 nn = i.normal;
    Vec3 sn = normalize(dpdu);
    Vec3 tn = cross(nn, sn);
    
    Vec3 tempDir(px, py, 0.f);
    tempDir.z = sqrtf(max(0.f, 1.f - tempDir.x*tempDir.x - tempDir.y*tempDir.y));

    //Local to world
    return Vec3(sn.x*tempDir.x + tn.x*tempDir.y + nn.x*tempDir.z,
                sn.y*tempDir.x + tn.y*tempDir.y + nn.y*tempDir.z,
                sn.z*tempDir.x + tn.z*tempDir.y + nn.z*tempDir.z);*/
    return CosineSampleHemisphere(drand48(), drand48(), i.normal);
    
    /*Vec3 tempDir = UniformSampleHemisphere(drand48(), drand48()); 

    float px, py;
    ConcentricSampleDisk(drand48(), drand48(), &px, &py);

    Vec3 dpdu(-py, px, 0.f);
    Vec3 nn = i.normal;
    Vec3 sn = normalize(dpdu);
    Vec3 tn = cross(nn, sn);
    
    //Local to world
    return Vec3(sn.x*tempDir.x + tn.x*tempDir.y + nn.x*tempDir.z,
                sn.y*tempDir.x + tn.y*tempDir.y + nn.y*tempDir.z,
                sn.z*tempDir.x + tn.z*tempDir.y + nn.z*tempDir.z);*/

}
