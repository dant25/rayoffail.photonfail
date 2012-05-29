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



SpectralQuantity Material::sampleBRDF(Vec3 n, Vec3 indir, Vec3 *dir, ReflectivityType &rt) {
    //FIXME só isso?
    if(drand48() >= spec) {
        rt = DIFFUSE;
        CosineSampleHemisphere(drand48(), drand48(), n);
    } else {
        rt = SPECULAR;
        *dir = indir.getReflected(n);
    }
    //TODO considerar textura
    return kd;
}
