#include "Light.h"

Light::Light(const SpectralQuantity &intensity)
:	intensity(intensity)
{
}

SpectralQuantity Light::getIntensity() {
    return intensity;
}
