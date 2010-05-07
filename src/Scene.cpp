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
    //  testa visibilidade
    //  se é visível
    //      computa cor
            //TODO: interseção com a luz?
            Intersection lightIntersect;
            lightIntersect.normal = Vec3(0.0, 0.0, 0.0);
            lightIntersect.point = Vec3(0.0, 0.0, 0.0);
            //FIXME placeholder só pra poder fazer algo na função agora
            ls = obj->computeLocalShading(lightIntersect, SpectralQuantity(1.0, 1.0, 1.0), 
                                    SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0));
    //      traça raio refletido r
    //      Ray r = reflectedRay(i.normal);
    //      rs = this->render(r);

    //Combina de algum modo os valores de ls e rs e retorna a cor 
    //encontrada por aquele raio na cena
    
    return ls; 
}

void Scene::addObject(Object *obj) {
   objects.addObject(obj);
}
