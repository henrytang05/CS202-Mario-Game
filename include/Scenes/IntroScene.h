#ifndef INTROSCENE_H
#define INTROSCENE_H

#include "Scene.h"

namespace SceneSpace {

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  void Update() override;

private:
};
} // namespace SceneSpace
#endif // INTROSCENE_H
