#ifndef SCENE_H
#define SCENE_H
#include "pch.h"
namespace SceneSpace {

enum SceneType : uint8_t { INTRO = 0, GAME };

class Scene {
public:
  virtual ~Scene();
  virtual Shared<Scene> update() = 0;
  virtual void draw() = 0;
  virtual void loadResources() = 0;
  virtual void start() = 0;
  // virtual bool isFinished() = 0;
  
protected:
};
} // namespace SceneSpace

#endif // SCENE_H
