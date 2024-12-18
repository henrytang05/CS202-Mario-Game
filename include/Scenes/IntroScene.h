#ifndef INTROSCENE_H
#define INTROSCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"
namespace SceneSpace {

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  Shared<Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;

private:
  bool changeGameScreen, changeLoadScreen, changeRankingScreen,
      changeSettingsScreen;
  Texture background;
  GUI::ImageButton *NewGameButton;
  GUI::ImageButton *LoadGameButton;
  GUI::ImageButton *RankingButton;
  GUI::ImageButton *SettingsButton;
};
} // namespace SceneSpace
#endif // INTROSCENE_H
