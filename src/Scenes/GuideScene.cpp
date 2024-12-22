#include "Scenes/GuideScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"

SceneSpace::GuideScene::GuideScene() {
}

SceneSpace::GuideScene::~GuideScene()
{
    #ifdef _DEBUG
    Log("GuideScene destroyed");
    #endif
}

Unique<SceneSpace::Scene> SceneSpace::GuideScene::updateScene(float deltaTime)
{
    SoundCtrl.Update();
    // for (auto &entity : entities) {
    //     entity->update(deltaTime);
    // }
    Vector2 mousePos = GetMousePosition();
    bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    return nullptr;
}

void SceneSpace::GuideScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
    // for (auto &entity : entities) {
    //     if (entity != nullptr)
    //     entity->draw();
    // }
}

void SceneSpace::GuideScene::loadResources()
{
    background = LoadTexture("./assets/GuideBackground.png");
}

void SceneSpace::GuideScene::init()
{
    // entityFactory = std::make_unique<EntityFactory>();
    // player = entityFactory->createMario();
    // entities.push_back(player);
    // for (auto &entity : entities) {
    //     if (entity->hasComponent<CollisionComponent>()) {
    //     entity->getComponent<CollisionComponent>().setEntities(
    //         Shared<std::vector<Shared<AbstractEntity>>>(&entities));
    //     }
    // }
}

