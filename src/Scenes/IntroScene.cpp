#include "Scenes/IntroScene.h"
#include "Logger.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"
namespace SceneSpace {
IntroScene::IntroScene() : Scene() {
  changeGameScreen = false;
  changeLoadScreen = false;
  changeRankingScreen = false;
  changeSettingsScreen = false;
  SoundCtrl.PlayGroundTheme();
}
IntroScene::~IntroScene() {
#ifdef _DEBUG
  Log("IntroScene destroyed");
#endif
  delete NewGameButton;
  delete LoadGameButton;
  delete RankingButton;
  delete SettingsButton;
}

Shared<Scene> IntroScene::updateScene() {
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  NewGameButton->update(mousePos, isLeftClick);
  LoadGameButton->update(mousePos, isLeftClick);
  RankingButton->update(mousePos, isLeftClick);
  SettingsButton->update(mousePos, isLeftClick);

  if (NewGameButton->isPressed())
    changeGameScreen = true;
  if (LoadGameButton->isPressed())
    changeLoadScreen = true;
  if (RankingButton->isPressed())
    changeRankingScreen = true;
  if (SettingsButton->isPressed())
    changeSettingsScreen = true;

  if (changeGameScreen)
    return std::make_shared<SceneSpace::GameScene>();
  return nullptr;
}
void IntroScene::draw() {
  DrawTexture(background, 0, 0, WHITE);
  NewGameButton->draw();
  LoadGameButton->draw();
  RankingButton->draw();
  SettingsButton->draw();
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
};
void IntroScene::init() {
  changeGameScreen = false;
  changeLoadScreen = false;
  changeRankingScreen = false;
  changeSettingsScreen = false;
};
} // namespace SceneSpace
