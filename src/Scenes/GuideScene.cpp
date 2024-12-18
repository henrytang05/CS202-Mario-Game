#include "Scenes/GuideScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GuideScene.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"

SceneSpace::GuideScene::GuideScene() {
    SoundCtrl.PlayGroundTheme();
}

SceneSpace::GuideScene::~GuideScene()
{
    #ifdef _DEBUG
    Log("GuideScene destroyed");
    #endif
    delete QuitButton;
}

Shared<SceneSpace::Scene> SceneSpace::GuideScene::updateScene(float deltaTime)
{
    SoundCtrl.Update();
    for (auto &entity : entities) {
        entity->update(deltaTime);
    }
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

void SceneSpace::GuideScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
    QuitButton->draw();
    for (auto &entity : entities) {
        if (entity != nullptr)
        entity->draw();
    }
}

void SceneSpace::GuideScene::loadResources()
{
    background = LoadTexture("./assets/GuideBackground.png");
    QuitButton = new GUI::ImageButton(30, 20, "./assets/QuitButton.png",
                                       "./assets/Hover_QuitButton.png");
}

void SceneSpace::GuideScene::init()
{
    entityFactory = std::make_unique<EntityFactory>();
    player = entityFactory->createMario();
    entities.push_back(player);
    for (auto &entity : entities) {
        if (entity->hasComponent<CollisionComponent>()) {
        entity->getComponent<CollisionComponent>().setEntities(
            Shared<std::vector<Shared<AbstractEntity>>>(&entities));
        }
    }
}

