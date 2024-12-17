#include "Scenes/GameScene.h"

#include <memory>

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/EnemyComponents.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EnemySystem.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
#include "pch.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera({0, 0}) {
  // TODO: remove this later
  enemyAISystem = createEnemyAISystem();
  enemyRenderSystem = createEnemyRenderSystem();
  enemyCollisionSystem = createEnemyCollisionSystem();
}

void GameScene::init() {
  time = 360.f;
  entityFactory = std::make_unique<EntityFactory>();
  player = entityFactory->createMario();
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
  // Loading BackGround
  Image bImage = LoadImage("Map/BackGroundnew.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  // Create Map
  entities = mapRenderer.createMap("Map/Level1new.json");

  // TODO: remove this later

  testEnemyCreated();
}

// TODO: remove this later
void GameScene::testEnemyCreated() {
  std::vector<std::vector<Shared<AbstractEntity>>::iterator> its;
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    Shared<AbstractEntity> entity = *it;
    if (!entity)
      continue;
    if (entity->hasComponent<EnemyTag>()) {
      enemies.push_back(entity);
      entity->getComponent<CollisionComponent>().setEntities(
          (Shared<std::vector<Shared<AbstractEntity>>>)&entities);
      its.push_back(it);
    }
  }
  for (auto it : its) {
    entities.erase(it);
  }
}

void GameScene::drawEnemies() {
  for (auto &enemy : enemies) {
    if (!enemy->isActive())
      continue;
    EnemyPosition &position = enemy->getComponent<EnemyPosition>();
    EnemyVelocity &velocity = enemy->getComponent<EnemyVelocity>();
    TextureComponent &texture = enemy->getComponent<TextureComponent>();
    enemyRenderSystem(position, velocity, texture, time);
  }
}
void GameScene::draw() {
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);
  // TODO: remove this later
  drawEnemies();
  for (auto &entity : entities) {
    if (entity != nullptr && entity->isActive())
      entity->draw();
  }
  EndMode2D();
  // TODO: remove this later
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE,
           WHITE);
}
Shared<Scene> GameScene::updateScene() {
  this->update();
  return nullptr;
}

// TODO: remove this later
void GameScene::updateEnemies() {
  for (auto &enemy : enemies) {
    if (!enemy->isActive())
      continue;
    EnemyPosition &position = enemy->getComponent<EnemyPosition>();
    EnemyVelocity &velocity = enemy->getComponent<EnemyVelocity>();
    EnemySize &size = enemy->getComponent<EnemySize>();
    CollisionComponent &collision = enemy->getComponent<CollisionComponent>();
    TextureComponent &texture = enemy->getComponent<TextureComponent>();
    this->enemyAISystem(position, velocity, size);
    // this->enemyCollisionSystem(collision, position, velocity, texture,
    // *enemy);
  }
}
void GameScene::update() {
  time -= GUI::get_delta_time();

  updateEnemies();

  for (auto &entity : entities) {
    if (entity->isActive())
      entity->update();
  }

  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= screenWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth - screenWidth / (2.0f * camera.zoom);
  SoundCtrl.Update((int)time);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
