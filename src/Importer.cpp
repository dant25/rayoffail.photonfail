#include "Importer.h"
#include "util/tinyxml/tinyxml.h"

//FIXME só tá aqui pra debugar
#include <iostream>

static void Importer::load(const char* path) {
   TiXmlDocument dae(path);

   if (!dae.LoadFile(path)){
      std::cout << "Arquivo inválido" << path << std::endl;
      return 0;
   }

   TiXmlElement* collada = dae.FirstChildElement("COLLADA");
   if (!collada)
      return 0;

   TiXmlElement* library_geometries = collada->FirstChildElement("library_geometries");
   
   TiXmlElement* geometry = library_geometries->FirstChildElement("geometry");
   //TODO: instanciar cena e adicionar cada mesh à cena
   while (geometry){
      TiXmlElement* mesh = geometry->FirstChildElement("mesh");
      while(mesh){
         //TODO instanciar mesh
         std::string meshid = std::string(geometry->Attribute("id"));

         TiXmlElement* triangles = mesh->FirstChildElement("triangles");
         if (!triangles)
            break;

         while (triangles){

            triangles->NextSiblingElement("triangles");
         }
         mesh->NextSiblingElement("mesh");
      }
      geometry->NextSiblingElement("geometry"); 
   }
}
