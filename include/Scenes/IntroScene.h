#ifndef INTROSCENE_H
#define INTROSCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"
namespace SceneSpace {

class IntroScene : public Scene {
public:
  IntroScene();
  ~IntroScene();
  Unique<Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;

private:
  Texture background;
  GUI::ImageButton *NewGameButton;
  GUI::ImageButton *LoadGameButton;
  GUI::ImageButton *RankingButton;
  GUI::ImageButton *SettingsButton;
  GUI::ImageButton *GuideButton;
  GUI::ImageButton *ResumeButton;
};
} // namespace SceneSpace
#endif // INTROSCENE_H
