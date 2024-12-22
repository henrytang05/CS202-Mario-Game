#include "Scenes/GameScene.h"

#include <memory>

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/EnemyComponents.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Entity/EnemySystem.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "System/System.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera({0, 0}), EM(EntityManager::get()) {
  // TODO: remove this later
  systems.push_back(std::make_unique<TransformSystem>());
  systems.push_back(std::make_unique<AnimationSystem>());
}

void GameScene::init() {
  time = 360.f;

  EntityFactory entityFactory;

  if (isMario)
    player = entityFactory.createMario();
  else
    player = entityFactory.createLuigi();

  gameOver = false;
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = EM.getComponent<PositionComponent>(&player).x;
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
  Image bImage = LoadImage("assets/Level2/BackGround.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  // Create Map
  entities = mapRenderer.createMap("assets/Level2/Level2.json");
}
void GameScene::draw() {
  float dt = GetFrameTime();
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);
  for (auto &entity : entities) {
    if (!entity->isActive())
      continue;
    if (entity->hasAllComponents<TextureComponent, PositionComponent>()) {
      systems[1]->update(entity, dt);
    }
    entity->draw();
  }
  EndMode2D();
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE,
           WHITE);
}
Unique<Scene> GameScene::updateScene(float deltaTime) {
  this->update(deltaTime);
  if (player->checkAlive() == false) {
    SoundCtrl.Pause();
  }
  if (player->checkOver()) {
    return make_unique<IntroScene>();
  }
  return nullptr;
}
void GameScene::update(float deltaTime) {
  time -= deltaTime;
  for (auto &entity : entities) {
    if (!entity->isActive())
      continue;
    entity->update(deltaTime);
    if (entity->hasAllComponents<TransformComponent, PositionComponent>())
      systems[0]->update(entity, deltaTime);
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
