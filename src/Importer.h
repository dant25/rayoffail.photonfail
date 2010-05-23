#ifndef IMPORTER_H_
#define IMPORTER_H_

#include "Scene.h"

//TODO: mais simples colocar só 1 função na classe Scene
class Importer {
   public:
      static Scene* load(const char* path);
};

#endif
