#include "Scene.h"
#include "math/Intersection.h"

using namespace std;

Scene::Scene() {
	background_color = SpectralQuantity(0.0, 0.0, 0.0);
	ambient_color = SpectralQuantity(0.01, 0.01, 0.01);
	maxDepth = 2;
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

	// Calcula a iluminação direta.
	for (int i = 0; i < lights.size(); i++) {
		//cout << "Intersectou!" << endl;
        //FIXME fazer vec retornado ter componente w = 1.0
		Vec3 samplePos = lights[i]->samplePoint();

		//FIXME calcula a normal previamente como o vetor que sai da luz
		//em direção ao ponto iluminado. Gambiarra para tratar luz pontual
		Vec3 lightNormal = objIntersect.point - samplePos;
		lightNormal.normalize();

		//FIXME passando normal por referencia
		lights[i]->getNormal(samplePos, lightNormal);

		Intersection lightIntersect;
		lightIntersect.point = samplePos;
        lightIntersect.point.w = 1.0;
		lightIntersect.normal = lightNormal;
		lightIntersect.dist = (lightIntersect.point - objIntersect.point).length();
         
		Ray shadowRay(objIntersect.point, normalize(lightIntersect.point - objIntersect.point));
		Object *shadowObj = objects.findObject(shadowRay);

		// Se não há obstáculo entre a luz e o ponto sendo considerado
		if (shadowObj) {
			if (shadowObj->getIntersection().dist < lightIntersect.dist) {
				continue;
			}
		}

		ls += obj->computeLocalShading(	objIntersect,
										lights[i]->getIntensity(normalize(objIntersect.point - lightIntersect.point)),
										normalize(samplePos - objIntersect.point),
										r.d*-1.0);
	}

	//Cor resultante de reflexão
	SpectralQuantity rs;

	if (depth < maxDepth && obj->getSpecularity() > 0.0) {
		Vec3 ref = (r.d * -1.0).getReflected(objIntersect.normal);
		rs = render(Ray(objIntersect.point, ref), depth + 1);
	}

	//Combina de algum modo os valores de ls e rs e retorna a cor
	//encontrada por aquele raio na cena
	SpectralQuantity result;
	result = ls * (1.0 - obj->getSpecularity()) + rs * obj->getSpecularity();

	return result + ambient_color;
}

void Scene::addObject(Object *obj) {
	objects.addObject(obj);
}

void Scene::addLight(Light *l) {
	lights.push_back(l);
	objects.addObject(l);
}

void Scene::addMaterial(const char *label, Material *m) {
   materials[std::string(label)] = m;
}

Material* Scene::getMaterial(const char *label) {
   return materials[label];
}
