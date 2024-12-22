#ifndef SCENE_H
#define SCENE_H

#include "SoundController.h"
namespace SceneSpace {

enum Type : uint8_t { INTRO = 0, GAME };

class Scene {
public:
  Scene();
  virtual ~Scene();
  virtual Unique<Scene> updateScene(float deltaTime) = 0;
  virtual void draw() = 0;
  virtual void loadResources() = 0;
  virtual void init() = 0;
  virtual void setEnd(bool end);
  virtual bool checkEnd();
  // virtual bool isFinished() = 0;

protected:
  bool isEnd = false;
  SoundController SoundCtrl;
};
} // namespace SceneSpace

#endif // SCENE_H
