#ifndef GAME_H
#define GAME_H

#include "pch.h"

#include "Scenes/Scene.h"
#include "globals.h"
#include <unordered_map>
using namespace SceneSpace;

class Game {
public:
  Game();
  ~Game();
  void Init();
  void Update();
  void Draw();
  void Clean();
  void Run();

private:
  SceneType m_currentSceneType;
  Weak<Scene> m_currentScene;
  std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
};

#endif // GAME_H
