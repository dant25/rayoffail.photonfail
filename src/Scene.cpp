#include "Scene.h"
#include "math/Intersection.h"

SpectralQuantity Scene::render(const Ray& r) const {
    Object *obj = objects.findObject(r);

    //Se não houver interseção, retorna cor de fundo
    if (!obj)
        return SpectralQuantity(0.0, 0.0, 0.0);

    Intersection i = obj->getIntersection();
    
    //Cor resultante da iluminação local
    SpectralQuantity ls;
    //Cor resultante de reflexão
    //SpectralQuantity rs;
    //para cada luz l
    for(int i = 0; i < lights.size(); i++) {
    //  TODO testa visibilidade
    //  se é visível
    //      computa cor
            //TODO: interseção com a luz?
            Vec3 samplePos = lights[i]->samplePoint();
            Vec3 lightNormal = i.pos - samplePos;
            //FIXME passnado normal por referencia
            lights[i]->getNormal(samplePos, lightNormal);
        
            //FIXME placeholder só pra poder fazer algo na função agora
            ls = obj->computeLocalShading(lightIntersect, SpectralQuantity(1.0, 1.0, 1.0), 
                                    SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0));
    //      traça raio refletido r
    //      Ray r = reflectedRay(i.normal);
    //      rs = this->render(r);
    }

    //Combina de algum modo os valores de ls e rs e retorna a cor 
    //encontrada por aquele raio na cena
    
    return ls; 
}

void Scene::addObject(Object *obj) {
   objects.addObject(obj);
}
