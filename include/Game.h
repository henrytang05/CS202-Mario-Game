#ifndef GAME_H
#define GAME_H
#include "Scenes/Scene.h"
class IUpdatable;
class IDrawable;
using namespace SceneSpace;
class Game : public IUpdatable, public IDrawable {
public:
  Game();
  ~Game();
  void init();
  void clean();
  void run();
  void update(float deltaTime) override;
  void draw() override;

private:
  Shared<SceneSpace::Scene> currentScene;
};

#endif // GAME_H
