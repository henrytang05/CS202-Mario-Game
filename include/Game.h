#ifndef GAME_H
#define GAME_H
#include "Interface.h"
#include "Scenes/Scene.h"
#include "GUI.h"
#include "pch.h"

class IUpdatable;
class IDrawable;

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
  GUI::ImageButton* YES;
  GUI::ImageButton* NO;
  Texture2D QuitGame;
  bool quittingGame = false;
};

#endif // GAME_H