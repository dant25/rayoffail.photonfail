#include "Importer.h"
#include "util/tinyxml/tinyxml.h"

//FIXME só tá aqui pra debugar
#include <iostream>
#include <string>

static void Importer::load(const char* path) {
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
   //TODO: instanciar cena 
   while (geometry){
      TiXmlElement* mesh = geometry->FirstChildElement("mesh");
      while(mesh){
         //TODO instanciar mesh e adicionar a cena
         std::string meshid = std::string(geometry->Attribute("id"));

         TiXmlElement* triangles = mesh->FirstChildElement("triangles");
         if (!triangles)
            break;

         while (triangles){
            TiXmlElement *input = triangles->FirstChildElement("input");
            while(input) {
                //TODO ler source com as coordenadas dos vertices
                std::cout << "input->semantic: " << input->Attribute("semantic") << std::endl;
                char *inputAttrName = input->Attribute("source");
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
                            char *posSourceName = inputVertSource->Attribute("source");
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
                            //FIXME quebrar string de coords e instanciar triangulos
                            std::cout << "\tfloat array: " << floatArray->GetText() << std::endl;
                        }
                        //FIXME NORMAL de novo?
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
                    //meshSource guarda um ponteiro para o source das positions
                    TiXmlElement *floatArray = meshSource->FirstChildElement("float_array");
                    //FIXME quebrar string de normais e instanciar triangulos
                    std::cout << "\tfloat array (normais): " << floatArray->GetText() << std::endl;
                    //FIXME NORMAL de novo?
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
                    std::cout << "\tfloat array (texcoord): " << floatArray->GetText() << std::endl;
                    //FIXME NORMAL de novo?
                }
                std::cout << "input->source: " << input->Attribute("source") << std::endl;
                input = input->NextSiblingElement("input");
            }
            //TODO ler source com as normais
            //TODO ler source com as coordenadas de textura
            TiXmlElement *p = triangles->FirstChildElement("p");
            //FIXME: quebrar a string de vertices e instanciar mesh
            std::cout << "Vertices dos triangulos: " << p->GetText() << std::endl;
            triangles = triangles->NextSiblingElement("triangles");
         }
         mesh = mesh->NextSiblingElement("mesh");
      }
      geometry = geometry->NextSiblingElement("geometry"); 
   }
}
