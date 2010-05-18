#include "Light.h"

Light::Light(const SpectralQuantity &intensity)
:	Object(Material(intensity, intensity, intensity, 0.0, 0.0)),
	intensity(intensity)
{
}

SpectralQuantity Light::getIntensity() {
    return intensity;
}
