#include <iostream>
#include "Renderer.h"
#include "objects/Sphere.h"

int main () {
    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    //Inicializa camera
    Camera c(300, 300, Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
    //Inicializa cena
    Sphere sphere(5.0, Vec3(0.0, 0.0, -7.0));
    Scene s;
    s.addObject(&sphere);

    Renderer r;
    Image *img;
    img = r.render(s, c);
    img->save("teste1.tga");
    //FIXME seria mais intuitivo se render não tratasse da alocação da imagem
    delete img;
}
