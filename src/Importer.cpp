#include "Importer.h"
#include "util/tinyxml/tinyxml.h"

//FIXME só tá aqui pra debugar
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "objects/Mesh.h"
#include "Material.h"
#include "SpectralQuantity.h"


//Funções auxiliares
void loadGeometry(TiXmlElement *libraryGeometries, Scene *s);
void loadMaterials(TiXmlElement *libraryMaterials, TiXmlElement *libraryEffects, Scene *s);
void loadColor(TiXmlElement *color, SpectralQuantity &sq);
void fixStr(char *str);


Scene* Importer::load(const char* path) {
   Scene *s = new Scene;
   TiXmlDocument dae(path);

   if (!dae.LoadFile(path)){
      std::cout << "Arquivo inválido" << path << std::endl;
      return 0;
   }

   //Verificando  o cabeçalho
   TiXmlElement* collada = dae.FirstChildElement("COLLADA");
   if (!collada)
      return 0;

   TiXmlElement* libraryMaterials = collada->FirstChildElement("library_materials");
   TiXmlElement* libraryEffects = collada->FirstChildElement("library_effects");
   loadMaterials(libraryMaterials, libraryEffects, s);

   TiXmlElement* libraryGeometries = collada->FirstChildElement("library_geometries");
   loadGeometry(libraryGeometries, s);

   return s;
}

void loadMaterials(TiXmlElement *libraryMaterials, TiXmlElement *libraryEffects, Scene *s) {
   TiXmlElement *material = libraryMaterials->FirstChildElement("material");
   while(material) {
      std::cout << "<material>" << std::endl;
      TiXmlElement *instanceEffect = material->FirstChildElement("instance_effect");
      //FIXME assumindo só 1 instance effect
      char *url = (char*) instanceEffect->Attribute("url");
      fixStr(url);
      std::cout << "\t<intance_effec url =  "  << url << ">" << std::endl;
      //TODO: encontrar effect
      TiXmlElement *effect = libraryEffects->FirstChildElement("effect");
      while(effect) {
         std::cout << "<effect id = " << effect->Attribute("id") << ">" << std::endl;
         if(strcmp(effect->Attribute("id"), url) == 0) {
            TiXmlElement *phong = effect->FirstChildElement("profile_COMMON")->FirstChildElement("technique")->FirstChildElement("phong");
            TiXmlElement *ambient = phong->FirstChildElement("ambient");
            TiXmlElement *color = ambient->FirstChildElement("color");
            SpectralQuantity ka;
            loadColor(color, ka);

            TiXmlElement *diffuse = phong->FirstChildElement("diffuse");
            color = diffuse->FirstChildElement("color");
            SpectralQuantity kd;
            loadColor(color, kd);

            TiXmlElement *specular = phong->FirstChildElement("specular");
            color = specular->FirstChildElement("color");
            SpectralQuantity ks;
            loadColor(color, ks);

            TiXmlElement *shininess = phong->FirstChildElement("shininess");
            TiXmlElement *value = shininess->FirstChildElement("float");
            float s = atof(value->GetText());

            TiXmlElement *reflectivity = phong->FirstChildElement("reflectivity");
            value = reflectivity->FirstChildElement("float");
            float spec = atof(value->GetText());
            
            Material *m = new Material(kd, ks, ka, s, spec);
            //TODO adicionar material à cena
         }
         effect = effect->NextSiblingElement("effect");
      }
      material = material->NextSiblingElement("material");
   }
}

void loadGeometry(TiXmlElement *libraryGeometries, Scene *s) {
   TiXmlElement* geometry = libraryGeometries->FirstChildElement("geometry");
   while (geometry){
      std::cout << "\t\tgeometry" << std::endl;
      TiXmlElement* mesh = geometry->FirstChildElement("mesh");
      while(mesh){
         std::cout << "\t\t\tmesh" << std::endl;
         Mesh *m = new Mesh;
         std::string meshid = std::string(geometry->Attribute("id"));
         TiXmlElement* triangles = mesh->FirstChildElement("triangles");

         while (triangles){
            TiXmlElement *input = triangles->FirstChildElement("input");
            int numOffset = 0;
            while(input) {
               numOffset++;
               //TODO ler source com as coordenadas dos vertices
               std::cout << "input->semantic: " << input->Attribute("semantic") << std::endl;
               char *inputAttrName = (char*)input->Attribute("source");
               fixStr(inputAttrName);
               if(strcmp(input->Attribute("semantic"), "VERTEX") == 0) {
                  //TODO procurar as coordenadas em mesh->source
                  //TODO agrupar em uma função
                  TiXmlElement *vertSource = mesh->FirstChildElement("vertices");
                  while(vertSource) {
                     if(strcmp(vertSource->Attribute("id"), inputAttrName) == 0) {
                        std::cout << "\tvertsource encontrado" << std::endl;
                        break;
                     }
                     vertSource = vertSource->NextSiblingElement("vertices");
                  }
                  //TODO ler cada input de vertSource
                  TiXmlElement *inputVertSource = vertSource->FirstChildElement("input");
                  while(inputVertSource) {
                     //TODO ler cada input, procurar o equivalente em mesh e ler o float_array
                     //POSITION
                     if(strcmp(inputVertSource->Attribute("semantic"), "POSITION") == 0) {
                        std::cout << "\tinput POSITION encontrado" << std::endl;
                        char *posSourceName = (char*)inputVertSource->Attribute("source");
                        fixStr(posSourceName);
                        
                        TiXmlElement *meshSource = mesh->FirstChildElement("source");
                        while(meshSource) {
                           if(strcmp(meshSource->Attribute("id"), posSourceName) == 0) {
                              std::cout << "\tsource de mesh encontrado" << std::endl;
                              break;
                           }
                           meshSource = meshSource->NextSiblingElement("source");
                        }
                        //meshSource guarda um ponteiro para o source das positions
                        TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                        int numVertexCoords = atoi(floatArray->Attribute("count"));
                        //char *coords = floatArray->GetText();
                        char *vertTok = strtok((char*)floatArray->GetText(), " ");
                        for(int i = 0; i < numVertexCoords/3; i++) {
                           float x = atof(vertTok);
                           vertTok = strtok(NULL, " ");
                           float y = atof(vertTok);
                           vertTok = strtok(NULL, " ");
                           float z = atof(vertTok);
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
                     if(strcmp(meshSource->Attribute("id"), inputAttrName) == 0) {
                        std::cout << "\tsource de mesh encontrado" << std::endl;
                        break;
                     }
                     meshSource = meshSource->NextSiblingElement("source");
                  }
                  TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                  int numNormalCoords = atoi(floatArray->Attribute("count"));
                  char *normalTok = strtok((char*)floatArray->GetText(), " ");
                  for(int i = 0;  i < numNormalCoords/3; i++) {
                     float x = atof(normalTok);
                     normalTok = strtok(NULL, " ");
                     float y = atof(normalTok);
                     normalTok = strtok(NULL, " ");
                     float z = atof(normalTok);
                     normalTok = strtok(NULL, " ");
                     m->addNormal(x, y, z);
                     std::cout << "addnormal: (" << x << ", " << y << ", " << z << ");" << std::endl;
                  }
                  //std::cout << "\tfloat array (normais): " << floatArray->GetText() << std::endl;
               }
               else if (strcmp(input->Attribute("semantic"), "TEXCOORD") == 0) {
                  TiXmlElement *meshSource = mesh->FirstChildElement("source");
                  while(meshSource) {
                     if(strcmp(meshSource->Attribute("id"), inputAttrName) == 0) {
                        std::cout << "\tsource de mesh encontrado" << std::endl;
                        break;
                     }
                     meshSource = meshSource->NextSiblingElement("source");
                  }
                  //meshSource guarda um ponteiro para o source das positions
                  TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                  //FIXME quebrar string de normais e instanciar triangulos
                  int numTexCoords = atoi(floatArray->Attribute("count"));
                  char *texTok = strtok((char*)floatArray->GetText(), " ");
                  for(int i = 0;  i < numTexCoords/2; i++) {
                     float x = atof(texTok);
                     texTok = strtok(NULL, " ");
                     float y = atof(texTok);
                     //m->addNormal(x, y);
                     //TODO: triangle[i]->addTexCoord(x, y);

                     std::cout << "addtexcoord: (" << x << ", " << y << ");" << std::endl;
                  }
                  //std::cout << "\tfloat array (texcoord): " << floatArray->GetText() << std::endl;
               }
               std::cout << "input->source: " << input->Attribute("source") << std::endl;
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
               /*else if (numOffset == 3) {
                 float vertId1 = atoi(tok);
                 tok = strtok(NULL, " ");
                 float vertNorm1 = atoi(tok);
                 tok = strtok(NULL, " ");
                 float vertId2 = atoi(tok);
                 tok = strtok(NULL, " ");
                 float vertNorm2 = atoi(tok);
                 tok = strtok(NULL, " ");
                 float vertId3 = atoi(tok);
                 tok = strtok(NULL, " ");
                 float vertNorm3 = atoi(tok);
                 }*/
            }
            //std::cout << "Vertices dos triangulos: " << p->GetText() << std::endl;

            triangles = triangles->NextSiblingElement("triangles");
         }
         std::cout << "\t\t ADD MESH" << std::endl;
         s->addObject(m);
         mesh = mesh->NextSiblingElement("mesh");
      }
      geometry = geometry->NextSiblingElement("geometry"); 
   }
}

void loadColor(TiXmlElement *color, SpectralQuantity &sq) {
   char *tok = strtok((char *) color->GetText(), " ");
   
   //FIXME desconsiderando o alpha da cor
   for(int i = 0; i < 3; i++) {
      sq.data[i] = atof(tok);
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
