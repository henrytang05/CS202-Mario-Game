#ifndef INTROSCENE_H
#define INTROSCENE_H
#include "GUI.h"
namespace SceneSpace {
class Scene;

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  Shared<Scene> update() override;
  void draw() override;
  void acceptInputHandler(InputHandler inputHandler) override;
  void loadResources() override;
  void start() override;
private:
  bool changeGameScreen, changeLoadScreen, changeRankingScreen, changeSettingsScreen;
  Texture background;
  GUI::ImageButton* NewGameButton;
  GUI::ImageButton* LoadGameButton;
  GUI::ImageButton* RankingButton;
  GUI::ImageButton* SettingsButton;
};
} // namespace SceneSpace
#endif // INTROSCENE_H


