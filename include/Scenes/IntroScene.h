#ifndef INTROSCENE_H
#define INTROSCENE_H

#include "Scene.h"

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  void Update() override;

private:
};
#endif // INTROSCENE_H
