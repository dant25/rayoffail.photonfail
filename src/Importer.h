#ifndef IMPORTER_H_
#define IMPORTER_H_

#include "Scene.h"
#include "Camera.h"

//TODO: mais simples colocar só 1 função na classe Scene
class Importer {
   public:
      static void load(const char* path, Scene** s, Camera** c);
};

#endif
