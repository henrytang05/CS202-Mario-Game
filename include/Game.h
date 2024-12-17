#ifndef GAME_H
#define GAME_H
#include "Interface.h"
#include "Scenes/Scene.h"
class IUpdatable;
class IDrawable;

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
};

#endif // GAME_H
