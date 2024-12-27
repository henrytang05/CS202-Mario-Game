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
}

Unique<SceneSpace::Scene> SceneSpace::LoadGameScene::updateScene(float deltaTime)
{
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

  return nullptr;
}

void SceneSpace::LoadGameScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
}

void SceneSpace::LoadGameScene::loadResources()
{
    background = LoadTexture("./assets/LoadGameBackground.png");                                       
}

void SceneSpace::LoadGameScene::init()
{
}
