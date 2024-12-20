#include "Scenes/GameScene.h"

#include <memory>

#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera({0, 0}) {}

void GameScene::init() {
  time = 360.f;
  entityFactory = std::make_unique<EntityFactory>();
  player = entityFactory->createLuigi();
  entities.push_back(player);
  gameOver = false;
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  camera.target.y = 784.0f - 186.0f;
  camera.zoom = 2.0f;
  SoundCtrl.PlayGroundTheme();
  for (auto &entity : entities) {
    if (entity->hasComponent<CollisionComponent>()) {
      entity->getComponent<CollisionComponent>().setEntities(
          Shared<std::vector<Shared<AbstractEntity>>>(&entities));
    }
  }
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  //Loading BackGround
  Image bImage = LoadImage("assets/Level1/BackGround.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  //Create Map
  entities = mapRenderer.createMap("assets/Level1/Level1new.json");
}
void GameScene::draw() {
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);
  for (auto &entity : entities) {
    if (entity != nullptr)
      entity->draw();
  }
  EndMode2D();
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE, WHITE);
}
Shared<Scene> GameScene::updateScene(float deltaTime) {
  this->update(deltaTime);
  return nullptr;
}
void GameScene::update(float deltaTime) {
  time -= GUI::get_delta_time();
  for (auto &entity : entities) {
    entity->update(deltaTime);
  }
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= gameWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = gameWidth - screenWidth / (2.0f * camera.zoom);
  SoundCtrl.Update((int)time);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
