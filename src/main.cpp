#include <iostream>
#include "Renderer.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"
#include "lights/QuadLight.h"
#include "lights/DiskLight.h"
#include "Importer.h"
#include "Transform.h"
int main () {

    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    //Inicializa camera
    Camera c(Vec3(0.0, -10.0, 9.0, 1.0), Vec3(0.0, 0.709, -0.709), Vec3(0.0, 0.709, 0.709), 500, 500);

    //Inicializa cena
    

    Scene *s = Importer::load("data/cena2.dae");
    Sphere sphere(Material(SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.0, 0.0, 0.0), 32.0, 0.1), 1.0, Vec3(0.0, 0.0, 1.0));
    sphere.t = translate(Vec3(2.0, 0.0, 1.0));
    //s->objects.objects[1]->t = translate(Vec3(3.0, 0.0, 2.0));
    s->addObject(&sphere);
    //s->addObject(new Sphere(Material(SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.7, 0.7, 0.0), SpectralQuantity(0.0, 0.0, 0.0), 32.0, 0.1), 1.0, Vec3(0.0, 0.0, 1.0)));
    //s.addObject(new Sphere(Material(SpectralQuantity(0.7, 0.0, 0.0), SpectralQuantity(0.7, 0.0, 0.0), SpectralQuantity(0.1, 0.1, 0.1), 32.0, 0.3), 5.0, Vec3(0.0, 0.0, 0.0)));


    s->addLight(new PointLight(Vec3(0.07625, 0.0, 5.90386), SpectralQuantity(0.7, 0.7, 0.7)));
    //s.addLight(new PointLight(Vec3(0.0, 35.0, 0.0), SpectralQuantity(1.0, 1.0, 1.0)));
    //s.addLight(new QuadLight(SpectralQuantity(1.0, 1.0, 1.0), Vec3(10.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), Vec3(0.5, 0.0, 1.0)));
    //s.addLight(new DiskLight(SpectralQuantity(1.0, 1.0, 1.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0), 2.0));


    Renderer r;
    Image *img;
    std::cout << "RAY OF FAIL!! ---->" << std::endl;    
    img = r.render(*s, c);
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
    delete s;
    delete img;
}
