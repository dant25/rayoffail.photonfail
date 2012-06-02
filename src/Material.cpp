#include "Material.h"
#include <cstdlib>
#include "math/Utilities.h"

Material::Material(const SpectralQuantity& kd, const SpectralQuantity& ks, const SpectralQuantity& ka, float shininess, float spec)
        : kd(kd), ks(ks), ka(ka), shininess(shininess), spec(spec){
	//SpectralQuantity sum = kd + ks + ka;
	//this->kd = kd/sum;
	//this->ks = ks/sum;
	//this->ka = ka/sum;
    tex = 0;
}



Vec3 Material::sampleBRDF(Vec3 n, Vec3 indir, Vec3 *dir, ReflectivityType &rt) {
    //FIXME só isso?
    if(drand48() >= spec) {
        rt = DIFFUSE;
        //*dir = CosineSampleHemisphere(drand48(), drand48(), n);
        Vec3 tempDir = UniformSampleHemisphere(drand48(), drand48()); 

        float px, py;
        ConcentricSampleDisk(drand48(), drand48(), &px, &py);

        Vec3 dpdu(-py, px, 0.f);
        Vec3 nn = n;
        Vec3 sn = normalize(dpdu);
        Vec3 tn = cross(nn, sn);

        //Local to world
        *dir = Vec3(tn.x*tempDir.x + sn.x*tempDir.y + nn.x*tempDir.z,
                tn.y*tempDir.x + sn.y*tempDir.y + nn.y*tempDir.z,
                tn.z*tempDir.x + sn.z*tempDir.y + nn.z*tempDir.z);
    } else {
        rt = SPECULAR;
        *dir = indir.getReflected(n);
    }
    //TODO considerar textura
    return Vec3(kd.data[0], kd.data[1], kd.data[2]);
}
