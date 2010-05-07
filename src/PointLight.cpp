#include "PointLight.h"

PointLight::PointLight(SpectralQuantity diffuse, SpectralQuantity specular, SpectralQuantity ambient)
    : Light(diffuse, specular, ambient) {

}

Vec3 PointLight::samplePoint() {
    return this->pos;
}

void PointLight::getNormal(Vec3 point, Vec3 &normal) {
}
