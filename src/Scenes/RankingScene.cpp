#include "Scenes/RankingScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"

SceneSpace::RankingScene::RankingScene() {
}

SceneSpace::RankingScene::~RankingScene()
{
    #ifdef _DEBUG
    Log("RankingScene destroyed");
    #endif
}

Unique<SceneSpace::Scene> SceneSpace::RankingScene::updateScene(float deltaTime)
{
  SoundCtrl.Update();
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

  return nullptr;
}

void SceneSpace::RankingScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
}

void SceneSpace::RankingScene::loadResources()
{
    background = LoadTexture("./assets/RankingBackground.png");                                       
}

void SceneSpace::RankingScene::init()
{
}
