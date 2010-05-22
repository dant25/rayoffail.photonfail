#include "Importer.h"
#include "util/tinyxml/tinyxml.h"

//FIXME só tá aqui pra debugar
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "objects/Mesh.h"

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

   TiXmlElement* libraryGeometries = collada->FirstChildElement("library_geometries");
   TiXmlElement* geometry = libraryGeometries->FirstChildElement("geometry");
   while (geometry){
      TiXmlElement* mesh = geometry->FirstChildElement("mesh");
      while(mesh){
         Mesh *m = new Mesh;
         s->addObject(m);
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
               if (inputAttrName[0] == '#'){
                  for( int i = 1; i < strlen(inputAttrName); i++)
                     inputAttrName[i-1] = inputAttrName[i];
                  inputAttrName[strlen(inputAttrName)-1] = '\0';
               }
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
                        //Remove o caractere # que aparece nos sources
                        if (posSourceName[0] == '#'){
                              for( int i = 1; i < strlen(posSourceName); i++)
                                 posSourceName[i-1] = posSourceName[i];
                              posSourceName[strlen(posSourceName)-1] = '\0';
                           }

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
                              m->addVertex(x, y, z);
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
                        m->addNormal(x, y, z);
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
                        std::cout << "tex coords: " << x << ", " << y << std::endl;
                     }
                     //std::cout << "\tfloat array (texcoord): " << floatArray->GetText() << std::endl;
                  }
                  std::cout << "input->source: " << input->Attribute("source") << std::endl;
                  input = input->NextSiblingElement("input");
               }
               TiXmlElement *p = triangles->FirstChildElement("p");
               //FIXME: quebrar a string de vertices e instanciar mesh
               int numTriangles = atoi(triangles->Attribute("count"));
               std::cout << "numTriIndices: " << numTriangles << std::endl;
               char *indexTok = strtok((char*)p->GetText(), " ");
            for(int i = 0;  i < numTriangles; i++) {
               if (numOffset == 2) {
                  float vertId1 = atoi(indexTok);
                  indexTok = strtok(NULL, " ");
                  float vertNorm1 = atoi(indexTok);
                  indexTok = strtok(NULL, " ");
                  float vertId2 = atoi(indexTok);
                  indexTok = strtok(NULL, " ");
                  float vertNorm2 = atoi(indexTok);
                  indexTok = strtok(NULL, " ");
                  float vertId3 = atoi(indexTok);
                  indexTok = strtok(NULL, " ");
                  float vertNorm3 = atoi(indexTok);
                  //TODO addFace
                  //m->addFace(x, y, z, 0);
                  //TODO: triangle[i]->addTexCoord(x, y);
                  //std::cout << "face indices: " << x << ", " << y << ", " << z << std::endl;
               }
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
         mesh = mesh->NextSiblingElement("mesh");
      }
      geometry = geometry->NextSiblingElement("geometry"); 
   }

   return s;
}
