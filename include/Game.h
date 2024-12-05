#ifndef GAME_H
#define GAME_H


#include "globals.h"
#include <unordered_map>
#include "Scenes/Scene.h"
using namespace SceneSpace;
class Game {
public:
  Game();
  ~Game();
  void init();
  void clean();
  void run();

private:
  Shared<SceneSpace::Scene> currentScene;
};

#endif // GAME_H
