#ifndef SCENE_H
#define SCENE_H
#include "pch.h"
#include "CommandListener.h"
#include "SoundController.h"

class InputHandler;
namespace SceneSpace {

enum SceneType : uint8_t { INTRO = 0, GAME };

class Scene : public CommandListener {
public:
  Scene();
  virtual ~Scene();
  virtual Shared<Scene> update() = 0;
  virtual void draw() = 0;
  virtual void acceptInputHandler(InputHandler inputHandler) = 0;
  virtual void loadResources() = 0;
  virtual void start() = 0;
  // virtual bool isFinished() = 0;
  
protected:
  SoundController SoundCtrl;
};
} // namespace SceneSpace

#endif // SCENE_H
