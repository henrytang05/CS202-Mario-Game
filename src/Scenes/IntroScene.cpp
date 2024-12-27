#include "Scenes/IntroScene.h"
#include "Logger.h"
#include "Scenes/ChooseThemeScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/GuideScene.h"
#include "Scenes/LoadGameScene.h"
#include "Scenes/Scene.h"
#include "Scenes/SettingScene.h"

namespace SceneSpace {
IntroScene::IntroScene() : Scene() { SoundCtrl.PlayGroundTheme(); }
IntroScene::~IntroScene() {
#ifdef _DEBUG
  Log("IntroScene destroyed");
#endif
  delete NewGameButton;
  delete LoadGameButton;
  delete RankingButton;
  delete SettingsButton;
  delete GuideButton;
  delete ResumeButton;
}

Unique<Scene> IntroScene::updateScene(float deltaTime) {
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  NewGameButton->update(mousePos, isLeftClick);
  LoadGameButton->update(mousePos, isLeftClick);
  RankingButton->update(mousePos, isLeftClick);
  SettingsButton->update(mousePos, isLeftClick);
  GuideButton->update(mousePos, isLeftClick);
  ResumeButton->update(mousePos, isLeftClick);

  if (NewGameButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>(true);
    // return std::make_unique<SceneSpace::ChooseThemeScene>();
  }
  if (LoadGameButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::LoadGameScene>();
  }
  if (RankingButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>(true);
  }
  if (SettingsButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::SettingScene>();
  }
  if (GuideButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GuideScene>();
  }

  if (ResumeButton->isPressed()) {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>(true);
  }

  return nullptr;
}
void IntroScene::draw() {
  DrawTexture(background, 0, 0, WHITE);
  NewGameButton->draw();
  LoadGameButton->draw();
  RankingButton->draw();
  SettingsButton->draw();
  GuideButton->draw();
}
void IntroScene::loadResources() {
  background = LoadTexture("./assets/MenuBackground.png");
  NewGameButton = new GUI::ImageButton(545, 340, "./assets/NewGameButton.png",
                                       "./assets/Hover_NewGameButton.png");
  LoadGameButton = new GUI::ImageButton(545, 425, "./assets/LoadGameButton.png",
                                        "./assets/Hover_LoadGameButton.png");
  RankingButton = new GUI::ImageButton(545, 510, "./assets/RankingButton.png",
                                       "./assets/Hover_RankingButton.png");
  SettingsButton = new GUI::ImageButton(545, 595, "./assets/SettingsButton.png",
                                        "./assets/Hover_SettingsButton.png");
  GuideButton = new GUI::ImageButton(30, 20, "./assets/GuideButton.png",
                                     "./assets/Hover_GuideButton.png");
  ResumeButton = new GUI::ImageButton(30, 80, "./assets/ResumeButton.png",
                                      "./assets/Hover_NewGameButton.png");
};
void IntroScene::init() {};
} // namespace SceneSpace
