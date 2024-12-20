#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H
#include "GUI.h"
#include "Scenes/Scene.h"

namespace SceneSpace {
class SettingScene : public Scene {
public:
  SettingScene();
  ~SettingScene();
  Shared<SceneSpace::Scene> updateScene(float deltaTime) override;
  void draw() override;
  void loadResources() override;
  void init() override;
  void update(float deltaTime);
private:
  Texture background;
  GUI::ImageButton* QuitButton;
  GUI::Slider* musicSetting;
  GUI::Slider* soundSetting;
  GUI::TickBox* mario;
  GUI::TickBox* luigi;
};
} // namespace SceneSpace
#endif // SETTINGSCENE_H
