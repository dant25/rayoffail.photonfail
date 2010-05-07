#include "Light.h"

Light::Light(SpectralQuantity diffuse, SpectralQuantity specular, SpectralQuantity ambient)
    : diff(diffuse), spec(specular), amb(ambient){
}

SpectralQuantity Light::getDiffIntensity() {
    return diff;
}

SpectralQuantity Light::getSpecIntensity() {
    return spec;
}

SpectralQuantity Light::getAmbIntensity() {
    return amb;
}
