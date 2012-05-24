#include <iostream>
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Importer.h"
#include "Image.h"


int main(int argc, char** argv) {
    //Verificar argumentos
    std::cout << "argc: " << argc << std::endl;
    for(int i = 1; i < argc; i++)
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    //Importar a cena
    Scene *scene;
    Camera *camera;
    Importer::load(argv[1], &scene, &camera);

    //Renderizar
    camera->setResolution(800, 800);

    Renderer renderer;
    Image *img = renderer.render(*scene, *camera);

    int numSamples = 10;

    for(int i = 1; i <= numSamples; i++) {
       Image *aux = renderer.render(*scene, *camera);
       for(int j = 0; j < img->getWidth(); j++) {
            for(int k = 0; k <  img->getHeight(); k++) {
                SpectralQuantity color = aux->getPixel(j, k);
                img->setPixel(j, k, (img->getPixel(j, k)*(i - 1.0) + color)/(float)i);
            }
       }
       delete aux;
    }

    //Salvar imagem
    img->save(argv[2]);

    return 0;
}
