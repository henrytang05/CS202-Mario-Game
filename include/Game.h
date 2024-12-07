#ifndef GAME_H
#define GAME_H

#include "Components/Camera.h"
#include "Scenes/Scene.h"

using namespace SceneSpace;
class Game : public IUpdatable, public IDrawable {
public:
  Game();
  ~Game();
  void init();
  void clean();
  void run();
  void update() override;
  void draw() override;

private:
  Shared<SceneSpace::Scene> currentScene;
  CameraComponent camera;
};

#endif // GAME_H
