#include "Scene.h"
#include "math/Intersection.h"

#include <iostream>

Scene::Scene(){
   background_color = SpectralQuantity(0.0001, 0.0001, 0.0001);
   maxDepth = 4;
}


SpectralQuantity Scene::render(const Ray& r) const {
   return render(r, 0);
}


SpectralQuantity Scene::render(const Ray& r, int depth) const {
   // obj = 0 caso não haja interseção
   Object *obj = objects.findObject(r);

   //Se não houver interseção, retorna cor de fundo
   if (!obj)
      return background_color;

   Intersection objIntersect = obj->getIntersection();

   //Cor resultante da iluminação local
   SpectralQuantity ls;
   //para cada luz l
   for(int i = 0; i < lights.size(); i++) {
      //  TODO testa visibilidade
      //  se é visível
      //      computa cor
      //TODO: interseção com a luz?
      Vec3 samplePos = lights[i]->samplePoint();
      //FIXME calcula a normal previamente como o vetor que sai da luz
      //em direção ao ponto iluminado. Gambiarra para tratar luz pontual
      Vec3 lightNormal = objIntersect.point - samplePos;
      //FIXME passando normal por referencia9
      lights[i]->getNormal(samplePos, lightNormal);
      Intersection lightIntersect;
      lightIntersect.point = samplePos;
      lightIntersect.normal = lightNormal;
      //FIXME placeholder só pra poder fazer algo na função agora
      //FIXME passando r.o como vetor posição da camera, não funcionará em projeção ortogonal.
      //FIXME somar as contribuições de cada luz
      ls += obj->computeLocalShading(lightIntersect, lights[i]->getIntensity(), r.o);
      //      traça raio refletido r
      //      Ray r = reflectedRay(i.normal);
      //      rs = this->render(r);
   }


   //Cor resultante de reflexão
   SpectralQuantity rs;

   if(depth < maxDepth && obj->getSpecularity() > 0.0){
      Vec3 ref =  (r.d*-1.0).getReflected(objIntersect.normal);
      //std::cout << "Raio refletido = " << ref.x << ", " << ref.y << ", " << ref.z << std::endl;
      rs = render(Ray(objIntersect.point, ref), depth+1);
   }


   //Combina de algum modo os valores de ls e rs e retorna a cor 
   //encontrada por aquele raio na cena
   SpectralQuantity result;
   result = ls*(1.0 - obj->getSpecularity()) + rs*obj->getSpecularity();

   return result;
}

void Scene::addObject(Object *obj) {
   objects.addObject(obj);
}

void Scene::addLight(Light *l) {
   lights.push_back(l);
}
