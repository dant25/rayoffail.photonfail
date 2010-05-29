#include "Importer.h"
#include "util/tinyxml/tinyxml.h"

//FIXME só tá aqui pra debugar
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "objects/Object.h"
#include "objects/Mesh.h"
#include "objects/Sphere.h"
#include "Material.h"
#include "SpectralQuantity.h"
#include "Transform.h"
#include "math/Vec3.h"
#include "lights/Light.h"
#include "lights/DiskLight.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "Texture.h"
#include <map>
#include "math/Utilities.h"
#include "Camera.h"

using std::map;
using std::string;

//Funções auxiliares
Camera* loadCamera(TiXmlElement* collada);
void loadGeometry(TiXmlElement *collada, map<string, Object*>& objects, map<string, Material*>& materials);
void loadMaterials(TiXmlElement *collada, map<string, Material*>& materials);
void loadScene(TiXmlElement *collada, map<string, Object*>& objects, map<string, Light*>& lights, Scene *s);
void loadLight(TiXmlElement *collada, map<string, Light*>& lights);
Texture* loadTexture(TiXmlElement *collada, TiXmlElement* effect, const char* id);
Texture* loadImage(TiXmlElement *collada, const char *id);
void loadColor(TiXmlElement *color, SpectralQuantity &sq);
void fixStr(char *str);


void Importer::load(const char* path, Scene** s, Camera** c) {
   *s = new Scene;
   TiXmlDocument dae(path);

   if (!dae.LoadFile(path)){
      std::cout << "Arquivo inválido" << path << std::endl;
      return 0;
   }

   //Verificando  o cabeçalho
   TiXmlElement* collada = dae.FirstChildElement("COLLADA");
   if (!collada)
      return 0;

   std::cout << "ler a camera" << std::endl;
   *c = loadCamera(collada);
   std::cout << "camera lida" << std::endl;

   map<string, Material*> materials;
   loadMaterials(collada, materials);
   map<string, Object*> objects;
   loadGeometry(collada, objects, materials);
   map<string, Light*> lights;
   loadLight(collada, lights);
   loadScene(collada, objects, lights, *s);
}

//FIXME considerando só uma cena
void loadScene(TiXmlElement *collada, map<string, Object*>& objects, map<string, Light*>& lights, Scene *s) {
   TiXmlElement* libraryVisualScenes = collada->FirstChildElement("library_visual_scenes");
   TiXmlElement* visualScene = libraryVisualScenes->FirstChildElement("visual_scene");

   TiXmlElement* node = visualScene->FirstChildElement("node");
   while(node) {
      //Ler transformações
      TiXmlElement* t = node->FirstChildElement("translate");
      char* tTok = strtok((char*)t->GetText(), " ");
      float tr[3];
      for(int i = 0; i < 3; i++) {
         tr[i] = strToFloat(tTok);
         tTok = strtok(NULL, " ");
      }

      Transform translateTransform = translate(Vec3(tr[0], tr[1], tr[2]));

      //FIXME assumindo que a primeira rotação é rotZ
      TiXmlElement* rotz = node->FirstChildElement("rotate");
      //FIXME ignora os 3 primeros valores
      char* rotzTok = strtok((char*)rotz->GetText(), " ");
      rotzTok = strtok(NULL, " ");
      rotzTok = strtok(NULL, " ");
      rotzTok = strtok(NULL, " ");
      Transform rz = rotateZ(strToFloat(rotzTok));

      //FIXME assumindo que a segunda rotação é roty
      TiXmlElement* roty = rotz->NextSiblingElement("rotate");
      char* rotyTok = strtok((char*)roty->GetText(), " ");
      rotyTok = strtok(NULL, " ");
      rotyTok = strtok(NULL, " ");
      rotyTok = strtok(NULL, " ");
      Transform ry = rotateY(strToFloat(rotzTok));

      //FIXME assumindo que a terceira rotação é rotx
      TiXmlElement* rotx = roty->NextSiblingElement("rotate");
      char* rotxTok = strtok((char*)rotx->GetText(), " ");
      rotxTok = strtok(NULL, " ");
      rotxTok = strtok(NULL, " ");
      rotxTok = strtok(NULL, " ");
      Transform rx = rotateX(strToFloat(rotxTok));

      //Ler instance_geometry
      TiXmlElement* instanceGeometry = node->FirstChildElement("instance_geometry");
      if(instanceGeometry) {
         char *url = (char*) instanceGeometry->Attribute("url");
         fixStr(url);
         //Mesh *m = readGeometry(collada, url);
         Mesh *m = objects[string(url)];
         m->t = translateTransform;
         s->addObject(m);    
      }
      TiXmlElement* instanceLight = node->FirstChildElement("instance_light");
      if(instanceLight) {
         char* url = (char*) instanceLight->Attribute("url");
         fixStr(url);
         //Light l
         //Light *l = lights[string(url)];
         //if(l)
         s->addLight(lights[string(url)]);
      }
      //Ler instance_light
      //Ler instance_camera
      //Adicionar mesh à cena
      node = node->NextSiblingElement("node");
   }
}

void loadMaterials(TiXmlElement *collada, map<string, Material*>& materials) {
   TiXmlElement* libraryMaterials = collada->FirstChildElement("library_materials");
   TiXmlElement* libraryEffects = collada->FirstChildElement("library_effects");

   TiXmlElement *material = libraryMaterials->FirstChildElement("material");
   while(material) {
      char *matId = (char*) material->Attribute("id");
      TiXmlElement *instanceEffect = material->FirstChildElement("instance_effect");
      //FIXME assumindo só 1 instance effect
      char *url = (char*) instanceEffect->Attribute("url");
      fixStr(url);
      TiXmlElement *effect = libraryEffects->FirstChildElement("effect");
      while(effect) {
         if(strcmp(effect->Attribute("id"), url) == 0) {
            TiXmlElement *phong = effect->FirstChildElement("profile_COMMON")->FirstChildElement("technique")->FirstChildElement("phong");
            TiXmlElement *ambient = phong->FirstChildElement("ambient");
            TiXmlElement *color = ambient->FirstChildElement("color");
            SpectralQuantity ka;
            loadColor(color, ka);

            TiXmlElement *diffuse = phong->FirstChildElement("diffuse");
            TiXmlElement *texture = diffuse->FirstChildElement("texture");
            SpectralQuantity kd;
            Texture *tex = NULL;
            if(texture) {
               std::cout << "<loadTexture>" << std::endl;
               tex = loadTexture(collada, effect, texture->Attribute("texture"));
               std::cout << "</loadTexture>" << std::endl;
               kd = SpectralQuantity(0.0, 0.0, 0.0);
            }
            else {
               color = diffuse->FirstChildElement("color");
               loadColor(color, kd);
            }

            TiXmlElement *specular = phong->FirstChildElement("specular");
            color = specular->FirstChildElement("color");
            SpectralQuantity ks;
            loadColor(color, ks);

            TiXmlElement *shininess = phong->FirstChildElement("shininess");
            TiXmlElement *value = shininess->FirstChildElement("float");
            float matShininess = strToFloat(value->GetText());

            TiXmlElement *reflectivity = phong->FirstChildElement("reflectivity");
            value = reflectivity->FirstChildElement("float");
            float spec = strToFloat(value->GetText());

            //FIXME atribuir textura ao material!
            Material *m = new Material(kd, ks, ka, matShininess, spec);
            if(tex)
               m->tex = tex;
            std::cout << "adicionando material id: " << matId << std::endl;
            //s->addMaterial(matId, m);
            materials[string(matId)] = m;
         }
         effect = effect->NextSiblingElement("effect");
      }
      material = material->NextSiblingElement("material");
   }
}

void loadGeometry(TiXmlElement *collada, map<string, Object*>& objects, map<string, Material*>& materials) {
   TiXmlElement* libraryGeometries = collada->FirstChildElement("library_geometries");
   TiXmlElement* geometry = libraryGeometries->FirstChildElement("geometry");
   while (geometry){
      const char* geometryId = geometry->Attribute("id");

      TiXmlElement* sphere = geometry->FirstChildElement("sphere");
      if(sphere) {
         const char* matId = sphere->Attribute("material");
         TiXmlElement* radius = sphere->FirstChildElement("radius");
         float sphereRadius = strToFloat(radius->GetText());
         TiXmlElement* center = sphere->FirstChildElement("center");
         Vec3 sphereCenter(0.0, 0.0, 0.0, 1.0);
         char *pTok = strtok((char*) center->GetText(), " ");
         sphereCenter.x = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         sphereCenter.y = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         sphereCenter.z = strToFloat(pTok);

         Sphere *s = new Sphere(*(materials[string(matId)]), sphereRadius, sphereCenter);
         //FIXME considerar vetor de objects*
         objects[string(geometryId)] = s;
      }
      TiXmlElement* mesh = geometry->FirstChildElement("mesh");
      //FIXME tratando geometry id como mesh id
      if (mesh){
         TiXmlElement* triangles = mesh->FirstChildElement("triangles"); 
         const char* matId = triangles->Attribute("material");
         Mesh *m;
         if(matId != NULL) {
            m = new Mesh(*(materials[string(matId)]));
            std::cout << "mat != NULL" << std::endl;
         } else
            m = new Mesh;
         while (triangles){
            TiXmlElement *input = triangles->FirstChildElement("input");
            int numOffset = 0;
            while(input) {
               numOffset++;
               //TODO ler source com as coordenadas dos vertices
               char *inputAttrName = (char*)input->Attribute("source");
               fixStr(inputAttrName);
               if(strcmp(input->Attribute("semantic"), "VERTEX") == 0) {
                  //TODO procurar as coordenadas em mesh->source
                  //TODO agrupar em uma função
                  TiXmlElement *vertSource = mesh->FirstChildElement("vertices");
                  while(vertSource) {
                     if(strcmp(vertSource->Attribute("id"), inputAttrName) == 0) 
                        break;
                     vertSource = vertSource->NextSiblingElement("vertices");
                  }
                  //TODO ler cada input de vertSource
                  TiXmlElement *inputVertSource = vertSource->FirstChildElement("input");
                  while(inputVertSource) {
                     //TODO ler cada input, procurar o equivalente em mesh e ler o float_array
                     //POSITION
                     if(strcmp(inputVertSource->Attribute("semantic"), "POSITION") == 0) {
                        char *posSourceName = (char*)inputVertSource->Attribute("source");
                        fixStr(posSourceName);

                        TiXmlElement *meshSource = mesh->FirstChildElement("source");
                        while(meshSource) {
                           if(strcmp(meshSource->Attribute("id"), posSourceName) == 0) 
                              break;

                           meshSource = meshSource->NextSiblingElement("source");
                        }
                        //meshSource guarda um ponteiro para o source das positions
                        TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                        int numVertexCoords = atoi(floatArray->Attribute("count"));
                        //char *coords = floatArray->GetText();
                        char *vertTok = strtok((char*)floatArray->GetText(), " ");
                        for(int i = 0; i < numVertexCoords/3; i++) {
                           std::cout << "String: (" << vertTok << ");" << std::endl;
                           float x = strToFloat(vertTok);
                           vertTok = strtok(NULL, " ");
                           std::cout << "String: (" << vertTok << ");" << std::endl;
                           float y = strToFloat(vertTok);
                           vertTok = strtok(NULL, " ");
                           std::cout << "String: (" << vertTok << ");" << std::endl;
                           float z = strToFloat(vertTok);
                           vertTok = strtok(NULL, " ");
                           m->addVertex(x, y, z);

                           std::cout << "addvertex: (" << x << ", " << y << ", " << z << ");" << std::endl;
                        }
                        //std::cout << "\tfloat array: " << floatArray->GetText() << std::endl;
                     }
                     //FIXME mais algum tipo de tag pra ler?
                     inputVertSource = inputVertSource->NextSiblingElement("input");
                  }
               }
               else if (strcmp(input->Attribute("semantic"), "NORMAL") == 0) {
                  TiXmlElement *meshSource = mesh->FirstChildElement("source");
                  while(meshSource) {
                     if(strcmp(meshSource->Attribute("id"), inputAttrName) == 0) 
                        break;
                     meshSource = meshSource->NextSiblingElement("source");
                  }
                  TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                  int numNormalCoords = atoi(floatArray->Attribute("count"));
                  char *normalTok = strtok((char*)floatArray->GetText(), " ");
                  for(int i = 0;  i < numNormalCoords/3; i++) {
                     float x = strToFloat(normalTok);
                     normalTok = strtok(NULL, " ");
                     float y = strToFloat(normalTok);
                     normalTok = strtok(NULL, " ");
                     float z = strToFloat(normalTok);
                     normalTok = strtok(NULL, " ");
                     m->addNormal(x, y, z);
                     std::cout << "addnormal: (" << x << ", " << y << ", " << z << ");" << std::endl;
                  }
                  //std::cout << "\tfloat array (normais): " << floatArray->GetText() << std::endl;
               }
               else if (strcmp(input->Attribute("semantic"), "TEXCOORD") == 0) {
                  TiXmlElement *meshSource = mesh->FirstChildElement("source");
                  while(meshSource) {
                     if(strcmp(meshSource->Attribute("id"), inputAttrName) == 0) 
                        break;
                     meshSource = meshSource->NextSiblingElement("source");
                  }
                  //meshSource guarda um ponteiro para o source das positions
                  TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                  //FIXME quebrar string de normais e instanciar triangulos
                  int numTexCoords = atoi(floatArray->Attribute("count"));
                  char *texTok = strtok((char*)floatArray->GetText(), " ");
                  for(int i = 0;  i < numTexCoords/2; i++) {
                     float x = strToFloat(texTok);
                     texTok = strtok(NULL, " ");
                     float y = strToFloat(texTok);
                     texTok = strtok(NULL, " ");
                     m->addTexCoord(x, y);
                     std::cout << "addtexcoord: (" << x << ", " << y << ");" << std::endl;
                  }
                  //std::cout << "\tfloat array (texcoord): " << floatArray->GetText() << std::endl;
               }
               input = input->NextSiblingElement("input");
            }
            TiXmlElement *p = triangles->FirstChildElement("p");
            //FIXME: quebrar a string de vertices e instanciar mesh
            int numTriangles = atoi(triangles->Attribute("count"));
            std::cout << "numTriangles: " << numTriangles << std::endl;
            char *indexTok = strtok((char*)p->GetText(), " ");
            std::cout << "numOffset: " << numOffset << std::endl;
            for(int i = 0;  i < numTriangles; i++) {
               if (numOffset == 2) {
                  int vertId1 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm1 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertId2 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm2 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertId3 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm3 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  m->addFace(vertId1, vertId2, vertId3, vertNorm1, vertNorm2, vertNorm3);
                  std::cout << "addface: (" << vertId1  << ", " << vertId2 << ", " << vertId3 << ")" << std::endl;
               }
               //TODO ler texcoords
               else if (numOffset == 3) {
                  int vertId1 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm1 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int texCoord1 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertId2 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm2 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int texCoord2 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertId3 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int vertNorm3 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  int texCoord3 = atoi(indexTok);

                  indexTok = strtok(NULL, " ");
                  m->addFace(vertId1, vertId2, vertId3, vertNorm1, vertNorm2, vertNorm3, texCoord1, texCoord2, texCoord3);
                  std::cout << "addface: (" << vertId1  << ", " << vertId2 << ", " << vertId3 << ")" << std::endl;
               }
            }
            //std::cout << "Vertices dos triangulos: " << p->GetText() << std::endl;

            triangles = triangles->NextSiblingElement("triangles");
         }
         //s->addObject(m);
         //FIXME tratando geomtry id como meshId
         objects[string(geometryId)] = m;
      }
      geometry = geometry->NextSiblingElement("geometry"); 
   }
}


void loadLight(TiXmlElement *collada, map<string, Light*>& lights) {
   TiXmlElement* libraryLights = collada->FirstChildElement("library_lights");
   TiXmlElement* light = libraryLights->FirstChildElement("light");

   while(light) {
      char *lightId = (char*)light->Attribute("id");
      Light *l;
      //Ler disk light
      TiXmlElement* disk = light->FirstChildElement("technique_common")->FirstChildElement("disk");
      if(disk) {
         SpectralQuantity intensity;
         loadColor(disk->FirstChildElement("color"), intensity);

         //Lê o vetor centre
         TiXmlElement* diskCentre = disk->FirstChildElement("centre");
         Vec3 centre(0.0, 0.0, 0.0, 1.0);
         char *cTok = strtok((char*) diskCentre->GetText(), " ");
         centre.x = strToFloat(cTok);
         cTok = strtok(NULL, " ");
         centre.y = strToFloat(cTok);
         cTok = strtok(NULL, " ");
         centre.z = strToFloat(cTok);

         //Lê o vetor normal
         TiXmlElement* diskNormal = disk->FirstChildElement("normal");
         Vec3 normal(0.0, 0.0, 0.0);
         char *nTok = strtok((char*) diskNormal->GetText(), " ");
         normal.x = strToFloat(nTok);
         nTok = strtok(NULL, " ");
         normal.y = strToFloat(nTok);
         nTok = strtok(NULL, " ");
         normal.z = strToFloat(nTok);

         TiXmlElement* diskRadius = disk->FirstChildElement("radius");
         float radius = strToFloat(diskRadius->GetText());

         l = new DiskLight(intensity, centre, normal, radius);
         lights[string(lightId)] = l;
      }
      //Ler point light
      TiXmlElement* point = light->FirstChildElement("technique_common")->FirstChildElement("point");
      if(point) {
         SpectralQuantity intensity;
         loadColor(point->FirstChildElement("color"), intensity);

         //Lê o vetor pos
         TiXmlElement* pointPos = point->FirstChildElement("pos");
         Vec3 pos(0.0, 0.0, 0.0, 1.0);
         char *pTok = strtok((char*) pointPos->GetText(), " ");
         pos.x = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         pos.y = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         pos.z = strToFloat(pTok);

         l = new PointLight(pos, intensity);
         lights[string(lightId)] = l;
      }
      //Ler spot light
      TiXmlElement* spot = light->FirstChildElement("technique_common")->FirstChildElement("spot");
      if(spot) {
         SpectralQuantity intensity;
         loadColor(point->FirstChildElement("color"), intensity);

         //Lê o vetor pos
         TiXmlElement* spotPos = spot->FirstChildElement("pos");
         Vec3 pos(0.0, 0.0, 0.0, 1.0);
         char *pTok = strtok((char*) spotPos->GetText(), " ");
         pos.x = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         pos.y = strToFloat(pTok);
         pTok = strtok(NULL, " ");
         pos.z = strToFloat(pTok);

         //Lê direção do spot
         TiXmlElement* spotDir = spot->FirstChildElement("dir");
         Vec3 dir(0.0, 0.0, 0.0);
         char *dTok = strtok((char*) spotDir->GetText(), " ");
         dir.x = strToFloat(dTok);
         dTok = strtok(NULL, " ");
         dir.y = strToFloat(dTok);
         dTok = strtok(NULL, " ");
         dir.z = strToFloat(dTok);

         //Lê angulo do spot (em graus)
         TiXmlElement* spotAngle = spot->FirstChildElement("falloff_angle");
         float cutoff = strToFloat(spotAngle->GetText());

         //Lê expoente do spot
         TiXmlElement* spotExp = spot->FirstChildElement("falloff_exponent");
         float exp = strToFloat(spotExp->GetText());

         l = new SpotLight(intensity, pos, dir, cutoff, exp);
      }
      light = light->NextSiblingElement("light");
   }
}

Texture* loadTexture(TiXmlElement* collada, TiXmlElement *effect, const char* id) {
   //FIXME pegando o primeiro effect que não tem nada a ver com textura
   TiXmlElement* profileCommon = effect->FirstChildElement("profile_COMMON");

   TiXmlElement* newparam = profileCommon->FirstChildElement("newparam");
    std::cout << "prcurando id: " << id << std::endl;
   while(newparam) {
      std::cout << "newparam->sid: " << newparam->Attribute("sid") << std::endl;
      if(strcmp(id, newparam->Attribute("sid")) == 0) {
         std::cout << "found id: "  << id << std::endl;
         break;
      }
      newparam = newparam->NextSiblingElement("newparam");
   }
   
   std::cout << "a" << std::endl;
   TiXmlElement* sampler2D = newparam->FirstChildElement("sampler2D");
   std::cout << "a" << std::endl;
   TiXmlElement* samplerSouce = sampler2D->FirstChildElement("source");

   char* sourceid = (char*) samplerSouce->GetText();

   //FIXME ignorando filtros
   newparam = profileCommon->FirstChildElement("newparam");
   while(newparam) {
      if(strcmp(sourceid, newparam->Attribute("sid")) == 0) {
         std::cout << "sourceid: " << sourceid << std::endl;
         break;
      }
      newparam = newparam->NextSiblingElement("newparam");
   }

   std::cout << "a" << std::endl;
   TiXmlElement* surface = newparam->FirstChildElement("surface");
   TiXmlElement* initFrom = surface->FirstChildElement("init_from");

   //FIXME deveria retornar uma IMG
   //FIXME considerar <format>
   std::cout << "<loadImage>" << std::endl;
   std::cout << "initFrom: " << initFrom->GetText() << std::endl;
   Texture *tex = loadImage(collada, initFrom->GetText());
   std::cout << "</loadImage>" << std::endl;

   return tex;
}

Texture* loadImage(TiXmlElement *collada, const char *id) {
   TiXmlElement* libraryImages = collada->FirstChildElement("library_images");
   TiXmlElement* image = libraryImages->FirstChildElement("image");

   while(image) {
      if(strcmp(id, image->Attribute("id")) == 0) {
         std::cout << "image id: " << id << std::endl;
         break;
      }
      image = image->NextSiblingElement("image");
   }

   TiXmlElement* initFrom = image->FirstChildElement("init_from");
   std::cout << "carregando imagem: " << initFrom->GetText() << std::endl;
   Texture *tex = new Texture(initFrom->GetText());
   return tex;
}

//FIXME considerando só uma camera
Camera* loadCamera(TiXmlElement* collada) {
   TiXmlElement *libraryCameras = collada->FirstChildElement("library_cameras");
   TiXmlElement *camera = libraryCameras->FirstChildElement("camera");

   TiXmlElement* perspective = camera->FirstChildElement("optics")->FirstChildElement("technique_common")->FirstChildElement("perspective");
   
   std::cout << "ler pos" << std::endl;
   TiXmlElement* cPos = perspective->FirstChildElement("pos");
   Vec3 pos(0.0, 0.0, 0.0, 1.0);
   char *pTok = strtok((char*) cPos->GetText(), " ");
   pos.x = strToFloat(pTok);
   pTok = strtok(NULL, " ");
   pos.y = strToFloat(pTok);
   pTok = strtok(NULL, " ");
   pos.z = strToFloat(pTok);

   std::cout << "ler lookat" << std::endl;
   TiXmlElement* cLookat = perspective->FirstChildElement("lookat");
   Vec3 lookat;
   char *lTok = strtok((char*) cLookat->GetText(), " ");
   lookat.x = strToFloat(lTok);
   lTok = strtok(NULL, " ");
   lookat.y = strToFloat(lTok);
   lTok = strtok(NULL, " ");
   lookat.z = strToFloat(lTok);

   std::cout << "ler up" << std::endl;
   TiXmlElement* cUp = perspective->FirstChildElement("up");
   Vec3 up;
   char *upTok = strtok((char*) cUp->GetText(), " ");
   up.x = strToFloat(upTok);
   upTok = strtok(NULL, " ");
   up.y = strToFloat(upTok);
   upTok = strtok(NULL, " ");
   up.z = strToFloat(upTok);

   std::cout << "instanciar camera" << std:: endl;
   Camera *c = new Camera(pos, lookat, up);
   return c;
}

void loadColor(TiXmlElement *color, SpectralQuantity &sq) {
   char *tok = strtok((char *) color->GetText(), " ");

   //FIXME desconsiderando o alpha da cor
   for(int i = 0; i < 3; i++) {
      sq.data[i] = strToFloat(tok);
      tok = strtok(NULL, " ");
   }
}

void fixStr(char *str) {
   if (str[0] == '#'){
      for(int i = 1; i < strlen(str); i++)
         str[i-1] = str[i];
      str[strlen(str)-1] = '\0';
   }
}
