#include "Scenes/ChooseThemeScene.h"
#include "Logger.h"
#include "Scenes/GameScene.h"
#include "Scenes/Scene.h"


namespace SceneSpace {
ChooseThemeScene::ChooseThemeScene() : Scene() {
}
ChooseThemeScene::~ChooseThemeScene() {
#ifdef _DEBUG
  Log("ChooseThemeScene destroyed");
#endif
  delete Air;
  delete Water;
  delete Fire;
}

Unique<Scene> ChooseThemeScene::updateScene(float deltaTime) {
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  Air->update(mousePos, isLeftClick);
  Water->update(mousePos, isLeftClick);
  Fire->update(mousePos, isLeftClick);

  if (Air->isPressed())
  {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>("Level1", "Easy");
  }
  if (Water->isPressed())
  {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>("Level2", "Easy");
  }  
  if (Fire->isPressed())
  {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GameScene>("Level3", "Easy");
  }  
  return nullptr;
}
void ChooseThemeScene::draw() {
  DrawTexture(background, 0, 0, WHITE);
  Air->draw();
  Water->draw();
  Fire->draw();
}
void ChooseThemeScene::loadResources() {
  background = LoadTexture("./assets/MenuBackground.png");
  Air = new GUI::ImageButton(545, 340, "./assets/AirPrincess.png",
                                       "./assets/Hover_AirPrincess.png");
  Water = new GUI::ImageButton(545, 445, "./assets/WaterPrincess.png",
                                       "./assets/Hover_WaterPrincess.png");
  Fire = new GUI::ImageButton(545, 550, "./assets/FirePrincess.png",
                                       "./assets/Hover_FirePrincess.png");
};
void ChooseThemeScene::init() {
};
} // namespace SceneSpace
