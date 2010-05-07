#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_


class PointLight : public Light {
public:
    PointLight(SpectralQuantity diffuse, SpectralQuantity specular, SpectralQuantity ambient);

    Vec3 samplePoint();
    void getNormal(Vec3 point, Vec3 &normal);
private:
    Vec3 pos;
};


#endif
