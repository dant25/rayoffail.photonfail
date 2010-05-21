#include <iostream>
#include "Renderer.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"
#include "lights/QuadLight.h"


int main () {

    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    //Inicializa camera
    Camera c(Vec3(0.0, 0.0, 40.0), Vec3(0.0, 0.0, -1.0), Vec3(0.0, 1.0, 0.0), 500, 500);

    //Inicializa cena
    
    Scene s;
    //s.addObject(new Sphere(Material(SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.0, 0.0, 0.0), 32.0, 0.6), 4.0, Vec3(0.0, 15.0, 0.0)));
    s.addObject(new Sphere(Material(SpectralQuantity(0.7, 0.0, 0.0), SpectralQuantity(0.7, 0.0, 0.0), SpectralQuantity(0.0, 0.0, 0.0), 32.0, 0.0), 5.0, Vec3(0.0, 0.0, 0.0)));


    //s.addLight(new PointLight(Vec3(0.0, 0.0, 20.0), SpectralQuantity(0.7, 0.7, 0.7)));
    //s.addLight(new PointLight(Vec3(0.0, 35.0, 0.0), SpectralQuantity(1.0, 1.0, 1.0)));
    s.addLight(new QuadLight(SpectralQuantity(1.0, 1.0, 1.0), Vec3(10.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.5, 0.0, 1.0)));

    Renderer r;
    Image *img;
    img = r.render(s, c);
    img->save("teste1.tga");
    //FIXME seria mais intuitivo se render não tratasse da alocação da imagem

    /*
    Importer imp("/scene.obj");

    for(int i=0; i < imp.numObjects(); i++)
    {
    	s.addObject(imp.nextObjec());
    }
    */

    //Importer::load("data/triangle.dae");
    delete img;
}
