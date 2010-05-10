#include <iostream>
#include "Renderer.h"
#include "objects/Sphere.h"
#include "PointLight.h"

int main () {
    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    //Inicializa camera
    Camera c(600, 600, Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
    //Inicializa cena
    Material m(SpectralQuantity(0.7, .0, .0), SpectralQuantity(0.6, .0, .0), SpectralQuantity(0.5, .0, .0), 32.0);
    Sphere sphere(m, 5.0, Vec3(0.0, 0.0, -7.0));

    PointLight l(SpectralQuantity(0.8, 0.8, 0.8), SpectralQuantity(0.5, 0.5, 0.5), SpectralQuantity(0.4, 0.4, 0.4));
    l.pos = Vec3(3.0, 3.0, -1.0);

    Scene s;
    s.addObject(&sphere);
    s.addLight(&l);

    Renderer r;
    Image *img;
    img = r.render(s, c);
    img->save("teste1.tga");
    //FIXME seria mais intuitivo se render não tratasse da alocação da imagem
    delete img;
}
