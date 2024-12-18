#ifndef SCENE_H
#define SCENE_H

#include "SoundController.h"
namespace SceneSpace {

enum Type : uint8_t { INTRO = 0, GAME };

class Scene {
public:
  Scene();
  virtual ~Scene();
  virtual Shared<Scene> updateScene(float deltaTime) = 0;
  virtual void draw() = 0;
  virtual void loadResources() = 0;
  virtual void init() = 0;
  // virtual bool isFinished() = 0;

protected:
  SoundController SoundCtrl;
};
} // namespace SceneSpace

#endif // SCENE_H
