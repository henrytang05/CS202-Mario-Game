#include "Scenes/GameScene.h"

#include <memory>

#include "Entity/EntityFactory.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() : Scene() { init(); }

void GameScene::init() {
    entityFactory = std::make_unique<EntityFactory>();
    Shared<Entity> mario = entityFactory->createMario();
    // Shared<Entity> luigi = entityFactory->createLuigi();
    // Shared<Entity> goomba = entityFactory->createGoomba();

    entities.push_back(mario);
    // entities.push_back(luigi);
    // entities.push_back(goomba);
}

GameScene::~GameScene() {
#ifdef _DEBUG
    Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}
void GameScene::loadResources() {}
void GameScene::start() {
    gameOver = false;
    // characters = {
    //     make_shared<Character>("./assets/Luigi-Small", 11, Vector2{16, 23})};
}
void GameScene::draw() {
    for (auto &entity : entities) {
        entity->draw();
    }
    // for (Shared<Character> ch : characters) {
    //   ch->draw();
    // }
}
Shared<Scene> GameScene::update() {
    for (auto &entity : entities) {
        entity->update();
    }
    // for (Shared<Character> ch : characters) {
    //   ch->update();
    // }
    return nullptr;
}

bool GameScene::isFinished() { return gameOver; }
}  // namespace SceneSpace
