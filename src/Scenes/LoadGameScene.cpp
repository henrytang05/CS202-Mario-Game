#include "Scenes/LoadGameScene.h"

SceneSpace::LoadGameScene::LoadGameScene() {}

SceneSpace::LoadGameScene::~LoadGameScene()
{
}

Shared<SceneSpace::Scene> SceneSpace::LoadGameScene::updateScene(float deltaTime)
{
    return NULL;
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
