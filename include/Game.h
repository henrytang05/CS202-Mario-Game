#ifndef GAME_H
#define GAME_H

#include "pch.h"
#include "globals.h"
#include <unordered_map>
#include "InputHandler.h"
using namespace SceneSpace;
class Scene;
class Game {
public:
  Game();
  ~Game();
  void init();
  void clean();
  void run();

private:
  Shared<SceneSpace::Scene> currentScene;
  InputHandler inputHandler;
};

#endif // GAME_H
