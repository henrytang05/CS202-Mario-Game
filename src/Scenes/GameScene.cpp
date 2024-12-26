#include "Scenes/GameScene.h"
#include "EventManager.h"

#include <memory>

#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "EntityManager.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "System/System.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"
class TextureComponent;
namespace SceneSpace {
int GameScene::lives = 3;
GameScene::GameScene() : Scene(), EM(EntityManager::getInstance()) {
  // TODO: remove this later
  entityFactory = std::make_unique<EntityFactory>(EM);

  Shared<CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>();
  Shared<TransformSystem> transformSystem = std::make_shared<TransformSystem>();
  Shared<AnimationSystem> animationSystem = std::make_shared<AnimationSystem>();
  Shared<PlayerSystem> playerSystem = std::make_shared<PlayerSystem>();
  Shared<SwingSystem> swingSystem = std::make_shared<SwingSystem>();
  Shared<CoinSystem> coinSystem = std::make_shared<CoinSystem>();
  Shared<CollisionHandlingSystem> collisionHandlingSystem =
      std::make_shared<CollisionHandlingSystem>();
  Shared<BlockSystem> blockSystem = std::make_shared<BlockSystem>();
  systems.push_back(playerSystem);
  systems.push_back(collisionSystem);
  systems.push_back(transformSystem);
  systems.push_back(collisionHandlingSystem);
  systems.push_back(animationSystem);
  systems.push_back(blockSystem);
  systems.push_back(swingSystem);
  systems.push_back(coinSystem);
  update_systems.push_back(playerSystem);
  update_systems.push_back(collisionSystem);
  update_systems.push_back(transformSystem);
  update_systems.push_back(collisionHandlingSystem);
  update_systems.push_back(blockSystem);
  draw_systems.push_back(animationSystem);
  update_systems.push_back(swingSystem);
  update_systems.push_back(coinSystem);
}

void GameScene::init() {
  time = 360.f;

  // create player type?
  if (isMario)
    player = entityFactory->createMario();
  else
    player = entityFactory->createLuigi();

  gameOver = false;
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player.lock()->getComponent<PositionComponent>().x;
  camera.target.y = 784.0f - 186.0f;
  camera.zoom = 2.0f;
  SoundCtrl.PlayGroundTheme();
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
  EM.reset();
}
void GameScene::loadResources() {
  // Loading BackGround
  Image bImage = LoadImage("assets/Level1/BackGround.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  // Create Map
  entities = mapRenderer.createMap("assets/Level1/Level1.json");
}
void GameScene::draw() {
  float dt = GetFrameTime();
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);

  for (auto &system : draw_systems) {
    system.lock()->draw(dt);
  }

  EndMode2D();
  int scores =0;
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE,
           WHITE);
  DrawText(TextFormat("Lives: %03i", (int)lives), 1200 - 35 * 6, 35,
           GAMEPLAY_TEXT_SIZE, WHITE);
  DrawText(TextFormat("Score: %03i", (int)scores), 1200 - 35 * 12, 35, GAMEPLAY_TEXT_SIZE, WHITE);
}
Unique<Scene> GameScene::updateScene(float deltaTime) {
  this->update(deltaTime);
  if (player.lock()->hasComponent<PlayerTag>() == false) {
    sleep(1);
    lives -= 1;
    if (lives == 0) {
      lives = 3;
      return make_unique<SceneSpace::IntroScene>();
    }
    return make_unique<SceneSpace::GameScene>();
  }
  return nullptr;
}
void GameScene::update(float deltaTime) {
  time -= deltaTime;
  for (auto &system : update_systems) {
    system.lock()->update(deltaTime);
  }
  EventQueue &eventQueue = EventQueue::getInstance();
  eventQueue.processAllEvents();

  camera.target.x = player.lock()->getComponent<PositionComponent>().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= gameWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = gameWidth - screenWidth / (2.0f * camera.zoom);
  SoundCtrl.Update((int)time);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
