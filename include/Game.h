#ifndef GAME_H
#define GAME_H
#include "Scenes/Scene.h"
#include "GUI.h"
#include "pch.h"

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
  void pushScene(Shared<SceneSpace::Scene> scene);
  void popScene();
  void clearScene();
private:
  std::stack<Shared<SceneSpace::Scene>> scenes;
  GUI::ImageButton* QuitButton;
};

#endif // GAME_H
