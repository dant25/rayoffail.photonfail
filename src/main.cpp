#include <iostream>
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "Importer.h"
#include "Image.h"
#include <cstdlib>
#include "PhotonMap.h"



int main(int argc, char** argv) {
    Vec3 v(0.0, 1.0, 2.0);
    std::cout << v[0] << ", " << v[1] << ", "  << v[2] << std::endl;

    srand48(time(0));
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
    /*Image *img = renderer.render(*scene, *camera);

    int numSamples = 1;
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
    img->save(argv[2]);*/



    std::cout << "Começando a lançar os photons!" << std::endl;
    int nPhotons = 50000;
    std::cout << "nPhotons: " << nPhotons << std::endl;
    int photonCount = 0;
    //FIXME amostrar luz aleatoriamente no laço
    Light *l = scene->lights[0];
    std::vector<Photon> directMap;
    std::vector<Photon> causticMap;
    std::vector<Photon> indirectMap;
    while(photonCount < nPhotons) {
        //FIXME incrementar aqui só quando adicionar em algum vetor
        //photonCount++;
        Photon p; 
        //FIXME calcular melhor a estimativa de cor do photon
        p.power = l->getIntensity()/nPhotons;

        //escolher posição de origem e direção do photon - já implementado no rof
        p.pos = l->samplePoint();
        p.dir = l->sampleDir(); 

        //std::cout << "p.p: (" << p.p.x << ", " << p.p.y << "," << p.p.z << ")" << std::endl;
        //std::cout << "p.dir: (" << p.dir.x << ", " << p.dir.y << "," << p.dir.z << ")" << std::endl;

        //Agora vem o principal: ver a trajetória do photon na cena
        //O pbrt faz sempre 3 interseções, depois ele usa roleta russa pra saber se para
        //essa parte do código é bem clara
        int nIntersections = 0;
        //Enquanto o photon bater em algum obj da cena
        Object *obj;
        bool specularReflection = false;
        while( scene->intersect(Ray(p.pos, p.dir), &obj) ) {
            //std::cout << "teve interseção com a cena!" << std::endl;
            nIntersections++;
            Intersection objIntersect = obj->getIntersection();
            
            if(obj->getSpecularity() != 1.0) {
                if(nIntersections == 1){ //directHit em uma superfície com difusidade
                    //std::cout << "inserir no mapa direto" << std::endl;
                    directMap.push_back(p);
                }
                else if(specularReflection) //indirectHit, de superfície specular
                    causticMap.push_back(p);
                else //indirectHit, de superfície difusa
                    indirectMap.push_back(p);
                photonCount++;
            }
            Material m = obj->getMaterial();
            Vec3 newDir;
            ReflectivityType flag;
            Vec3 invDir = p.dir*-1.0f;
            float pDotN = dot(invDir, objIntersect.normal);
            p.power *= m.sampleBRDF(objIntersect.normal, invDir, &newDir, flag)*pDotN;
            //p.alpha *= m.sampleBRDF(objIntersect.normal, invDir, &newDir, flag);
            p.dir = newDir;

            if(flag == SPECULAR)
                specularReflection = true;
            else
                specularReflection = false;

            //parte fácil
            p.pos = objIntersect.point;

            if( nIntersections > 3  ) {
                //O melhor mesmo seria um breakzão logo e pronto
                float contProb = 0.5; //exemplo do pbrt
                if(drand48() > contProb)
                    break;
                p.power /= contProb;
            }
        }
    }
    
    std::cout << "photonCount: " << photonCount << std::endl;
    std::cout << "numero de photons diretos: " << directMap.size() << std::endl;
    std::cout << "numero de photons indiretos: " << indirectMap.size() << std::endl;
    std::cout << "numero de photons de caustics: " << causticMap.size() << std::endl;

    PhotonMap directPhotonMap(directMap);
    PhotonMap indirectPhotonMap(indirectMap);
    PhotonMap causticPhotonMap(causticMap);

    return 0;
}

