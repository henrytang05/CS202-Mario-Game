#ifndef SCENE_H
#define SCENE_H
#include "pch.h"

namespace SceneSpace {

enum SceneType : uint8_t { INTRO = 0, GAME };

class Scene {
public:
  virtual ~Scene();
  virtual void Update() = 0;
  // virtual bool isFinished() = 0;

protected:
};

} // namespace SceneSpace

#endif // SCENE_H
