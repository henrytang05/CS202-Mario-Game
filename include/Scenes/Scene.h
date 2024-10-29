#ifndef SCENE_H
#define SCENE_H
#include "pch.h"

class Scene {
public:
  ~Scene();
  virtual void Update() = 0;
  virtual bool isFinished() { return true; }

protected:
};

#endif // SCENE_H
