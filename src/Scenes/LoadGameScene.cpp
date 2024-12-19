#include "Scenes/LoadGameScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
SceneSpace::LoadGameScene::LoadGameScene() {
    SoundCtrl.PlayGroundTheme();
}

SceneSpace::LoadGameScene::~LoadGameScene()
{
    #ifdef _DEBUG
    Log("LoadGameScene destroyed");
    #endif
    delete QuitButton;
}

Shared<SceneSpace::Scene> SceneSpace::LoadGameScene::updateScene(float deltaTime)
{
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  QuitButton->update(mousePos, isLeftClick);

  if (QuitButton->isPressed())
  {
    SoundCtrl.PlayTingSound();
    return std::make_shared<SceneSpace::IntroScene>();
  }

  return nullptr;
}

void SceneSpace::LoadGameScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
    QuitButton->draw();
}

void SceneSpace::LoadGameScene::loadResources()
{
    background = LoadTexture("./assets/LoadGameBackground.png");
    QuitButton = new GUI::ImageButton(30, 20, "./assets/QuitButton.png",
                                       "./assets/Hover_QuitButton.png");
                                       
}

void SceneSpace::LoadGameScene::init()
{
}
