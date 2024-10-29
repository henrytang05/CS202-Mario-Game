#ifndef GAME_H
#define GAME_H
#include "Scenes/Scene.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"

class Game {
public:
  Game();
  void Init();
  void Update();
  void Draw();
  void Clean();
  void Run();

private:
  Unique<Scene> currentScene;
};

#endif // GAME_H
