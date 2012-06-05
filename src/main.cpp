#include <iostream>
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Importer.h"
#include "Image.h"
#include <cstdlib>
#include "PhotonMap.h"
#include <math/Utilities.h>



int main(int argc, char** argv) {
    srand48(time(0));
    //Importar a cena
    Scene *scene;
    Camera *camera;
    Importer::load(argv[1], &scene, &camera);
    scene->preprocess();

    //Renderizar
    camera->setResolution(500, 500);

    Renderer renderer;
    Image *img = renderer.render(*scene, *camera);

    int numSamples = 100;
    for(int i = 1; i <= numSamples; i++) {
       Image *aux = renderer.render(*scene, *camera);
       for(int j = 0; j < img->getWidth(); j++) {
            for(int k = 0; k <  img->getHeight(); k++) {
                SpectralQuantity color = aux->getPixel(j, k);
                img->setPixel(j, k, (img->getPixel(j, k)*(i - 1.0) + color)/(float)i);
            }
       }
       aux->save("preview2.tga");
       std::cout << "sample " << i << "terminado" << std::endl;
       delete aux;
    }

    //Salvar imagem
    img->save(argv[2]);

    return 0;
}

