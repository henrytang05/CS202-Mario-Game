#include "Scenes/GameScene.h"

#include <memory>

#include "Components/Camera.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera(addComponent<CameraComponent>()) {
  init();
}

void GameScene::init() {
  entityFactory = std::make_unique<EntityFactory>();
  Shared<Mario> mario = entityFactory->createMario();
  player = mario;
  // Shared<Entity> luigi = entityFactory->createLuigi();
  // Shared<Entity> goomba = entityFactory->createGoomba();
  entities.push_back(mario);
  camera.setTarget(*mario);

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
  BeginMode2D(camera);
  DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
  // for (auto &entity : entities) {
  //   entity->draw();
  // }
  camera.setTarget(*player);
  player->draw();

  DrawLine(0.0f, ground, screenWidth, ground, BLACK);
  ClearBackground(RAYWHITE);
  EndMode2D();
  // for (Shared<Character> ch : characters) {
  //   ch->draw();
  // }
}
Shared<Scene> GameScene::updateScene() {
  for (auto &entity : entities) {
    entity->update();
  }
  // for (Shared<Character> ch : characters) {
  //   ch->update();
  // }
  return nullptr;
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
