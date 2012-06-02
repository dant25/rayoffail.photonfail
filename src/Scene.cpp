#include "Scene.h"
#include "math/Intersection.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Scene::Scene() {
	background_color = SpectralQuantity(0.0, 0.0, 0.0);
	ambient_color = SpectralQuantity(0.01, 0.01, 0.01);
	maxDepth = 2;

    directWithPhotons = false;
    finalGather = false;
}

SpectralQuantity Scene::render(const Ray& r) const {
	return render(r, 0);
}


bool Scene::intersect(const Ray& r, Object **obj) const{
    *obj = objects.findObject(r);
    if(!(*obj))
        return false;
    return true;
}

SpectralQuantity Scene::render(const Ray& r, int depth) const {
	// obj = 0 caso não haja interseção
	//Object *obj = objects.findObject(r);
	Object *obj;

	//Se não houver interseção, retorna cor de fundo
	if (!intersect(r, &obj))
		return background_color;

	Intersection objIntersect = obj->getIntersection();

	//Cor resultante da iluminação local
	SpectralQuantity ls;
    

    if(!directWithPhotons) {
	// Calcula a iluminação direta.
        for (unsigned int i = 0; i < lights.size(); i++) {
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
    } else {
        Vec3 irradEst;
        directMap->irradianceEstimate(&irradEst, objIntersect.point, objIntersect.normal, 10.0, 100);
        ls = SpectralQuantity(irradEst.x, irradEst.y, irradEst.z)*obj->getMaterial().kd;
    }

	//Cor resultante de reflexão
	SpectralQuantity rs;

	if (depth < maxDepth && obj->getSpecularity() > 0.0) {
		Vec3 ref = (r.d * -1.0).getReflected(objIntersect.normal);
		rs = render(Ray(objIntersect.point, ref), depth + 1);
	}

    //Cor resultante da iluminação indireta difusa (photon mapping)
    SpectralQuantity is;
    if(!finalGather) {
        Vec3 irradEst;
        indirectMap->irradianceEstimate(&irradEst, objIntersect.point, objIntersect.normal, 10.0, 100);
        //FIXME considerar brdf do material?
        is = SpectralQuantity(irradEst.x, irradEst.y, irradEst.z);
    } //else {
        //Lançar raios e amostrar todas as contribuições (direta, indireta e caustics)
    //}


	//Combina de algum modo os valores de ls e rs e retorna a cor
	//encontrada por aquele raio na cena
	SpectralQuantity result;
	result = (ls + is);//*(1.0 - obj->getSpecularity()) + rs * obj->getSpecularity();
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

void Scene::preprocess() {
    std::cout << "Começando a lançar os photons!" << std::endl;
    int nPhotons = 1000000;
    std::cout << "nPhotons: " << nPhotons << std::endl;
    int photonCount = 0;
    //FIXME amostrar luz aleatoriamente no laço
    Light *l = lights[0];
    std::vector<Photon> directPhotons;
    std::vector<Photon> causticPhotons;
    std::vector<Photon> indirectPhotons;
    //FIXME calcular melhor a estimativa de cor do photon
    Vec3 tempPower = (l->getIntensity()*2000.0f)/nPhotons;
    std::cout << "photon initial power: " << tempPower.x << ", " << tempPower.y << ", " << tempPower.z << std::endl;
    while(photonCount < nPhotons) {
        Photon p; 
        p.pos = l->samplePoint();// + norm*0.0001;
        p.dir = l->sampleDir();
        p.dir.normalize();
        Vec3 tempLightNormal;
        l->getNormal(Vec3(), tempLightNormal);
        p.power = tempPower*fabs(dot(p.dir, tempLightNormal));
        //directPhotons.push_back(p);

        int nIntersections = 0;
        //Enquanto o photon bater em algum obj da cena
        Object *obj;
        bool specularReflection = false;
        while( intersect(Ray(p.pos, p.dir), &obj) ) {
            nIntersections++;

            Intersection objIntersect = obj->getIntersection();
            Material m = obj->getMaterial();
            Vec3 invDir = p.dir*-1.0f;
            ReflectivityType flag;
            Vec3 newDir;
            float pDotN = fabs(dot(invDir, objIntersect.normal));
            p.pos = objIntersect.point;// + objIntersect.normal*0.0001;

            if(obj->getSpecularity() != 1.0) {
                if(nIntersections == 1)
                    directPhotons.push_back(p);
                else if(specularReflection) //indirectHit, de superfície specular
                    causticPhotons.push_back(p);
                else //indirectHit, de superfície difusa
                    indirectPhotons.push_back(p);
                photonCount++;
            }
            p.power *= m.sampleBRDF(objIntersect.normal, invDir, &newDir, flag);
            p.power *= pDotN;
            p.dir = newDir;
            p.dir.normalize();

            if(flag == SPECULAR)
                specularReflection = true;
            else
                specularReflection = false;

            if( nIntersections > 3  ) {
                float contProb = 0.5; //exemplo do pbrt
                if(drand48() > contProb)
                    break;
                p.power /= contProb;
            }
        }
    }
    //std::cout << "directPhotons: " << directPhotons.size() << std::endl;
    //std::cout << "indirectPhotons: " << indirectPhotons.size() << std::endl;
    directMap = new PhotonMap(directPhotons);
    indirectMap = new PhotonMap(indirectPhotons);
    causticMap = new PhotonMap(causticPhotons);

    /*for(int i = 1; i <= directPhotons.size(); i++) {
        std::cout << "photon " << i << std::endl;
        std::cout << "\tpos " << directMap->photons[i].pos.x << " " 
                              << directMap->photons[i].pos.y << " "
                              << directMap->photons[i].pos.z << std::endl;
        std::cout << "\tdir " << directMap->photons[i].dir.x << " "
                              << directMap->photons[i].dir.y << " "
                              << directMap->photons[i].dir.z << std::endl;
        std::cout << "\tpower " << directMap->photons[i].power.x  << " "
                              << directMap->photons[i].power.y  << " "
                              << directMap->photons[i].power.z << std::endl;

    }*/
}
