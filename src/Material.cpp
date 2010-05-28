#include "Material.h"

Material::Material(const SpectralQuantity& kd, const SpectralQuantity& ks, const SpectralQuantity& ka, float shininess, float spec)
        : kd(kd), ks(ks), ka(ka), shininess(shininess), spec(spec){
	//SpectralQuantity sum = kd + ks + ka;
	//this->kd = kd/sum;
	//this->ks = ks/sum;
	//this->ka = ka/sum;
    tex = 0;
}
