#include "Material.h"

Material::Material(const SpectralQuantity& kd, const SpectralQuantity& ks, const SpectralQuantity& ka, float shininess) 
        : kd(kd), ks(ks), ka(ka), shininess(shininess){
}

