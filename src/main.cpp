#include <iostream>
#include "Renderer.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"

int main () {
    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    //Inicializa camera
    Camera c(600, 600, Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
    //Inicializa cena
    Material m(SpectralQuantity(0.7, .0, .0), SpectralQuantity(0.6, .0, .0), SpectralQuantity(0.5, .0, .0), 32.0);

    Scene s;
    s.addObject(new Sphere(m, 5.0, Vec3(0.0, 0.0, 7.0)));
    s.addObject(new Sphere(m, 5.0, Vec3(0.0, 0.0, -7.0)));
    s.addLight(new PointLight(Vec3(3.0, 3.0, -1.0), SpectralQuantity(0.8, 0.8, 0.8)));

    Renderer r;
    Image *img;
    img = r.render(s, c);
    std::cout << "RAY OF FAIL!! Salvando imagem...---->" << std::endl;
    img->save("teste1.tga");
    std::cout << "RAY OF FAIL!! Salvo...---->" << std::endl;
    //FIXME seria mais intuitivo se render não tratasse da alocação da imagem

    /*
    Importer imp("/scene.obj");

    for(int i=0; i < imp.numObjects(); i++)
    {
    	s.addObject(imp.nextObjec());
    }
    */

    delete img;
}
