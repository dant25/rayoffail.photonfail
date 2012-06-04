#include "PointLight.h"
#include "math/Utilities.h"
#include <cstdlib>
PointLight::PointLight(const Vec3 &pos, const SpectralQuantity &intensity)
:	Light(intensity),
 	position(pos)
{
}


bool PointLight::intersect(const Ray&){
	return false;
}


Vec3 PointLight::samplePoint() {
    return this->position;
}


void PointLight::getNormal(Vec3,  Vec3 &) {
}

Vec3 PointLight::sampleDir() {
    //Amostrar ponto no globo
    Vec3 tempDir = UniformSampleHemisphere(drand48(), drand48()); 
    float px, py;
    ConcentricSampleDisk(drand48(), drand48(), &px, &py);
    
    float prob = drand48();
    Vec3 nn;
    if(prob < 0.5f)
        nn = Vec3(0.0, 1.0, 0.0);
    else
        nn = Vec3(0.0, -1.0, 0.0);

    Vec3 dpdu(-py, px, 0.f);
    Vec3 sn = normalize(dpdu);
    Vec3 tn = cross(nn, sn);

    //Local to world
    return Vec3(sn.x*tempDir.x + tn.x*tempDir.y + nn.x*tempDir.z,
            sn.y*tempDir.x + tn.y*tempDir.y + nn.y*tempDir.z,
            sn.z*tempDir.x + tn.z*tempDir.y + nn.z*tempDir.z);

}
