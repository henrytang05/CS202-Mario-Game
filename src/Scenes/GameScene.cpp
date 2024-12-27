#include "Scenes/GameScene.h"

#include <iterator>
#include <memory>

#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "Exporter.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "ScoreManager.h"
#include "System/System.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"
class TextureComponent;
namespace SceneSpace {
int GameScene::lives = 3;
GameScene::GameScene(const std::string &_nameScene, const std::string &_level)
    : Scene(), EM(&EntityManager::getInstance()) {
  nameScene = _nameScene;
  level = _level;
  entityFactory = std::make_unique<EntityFactory>(*EM);
  Shared<CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>();
  Shared<TransformSystem> transformSystem = std::make_shared<TransformSystem>();
  Shared<AnimationSystem> animationSystem = std::make_shared<AnimationSystem>();
  Shared<PlayerSystem> playerSystem = std::make_shared<PlayerSystem>();
  Shared<SwingSystem> swingSystem = std::make_shared<SwingSystem>();
  Shared<CoinSystem> coinSystem = std::make_shared<CoinSystem>();
  Shared<FlagSystem> flagSystem = std::make_shared<FlagSystem>();
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
  systems.push_back(flagSystem);
  update_systems.push_back(playerSystem);
  update_systems.push_back(collisionSystem);
  update_systems.push_back(transformSystem);
  update_systems.push_back(collisionHandlingSystem);
  update_systems.push_back(blockSystem);
  draw_systems.push_back(animationSystem);
  update_systems.push_back(swingSystem);
  update_systems.push_back(coinSystem);
  update_systems.push_back(flagSystem);
}
GameScene::GameScene() : Scene(), EM(&EntityManager::getInstance()) {}
GameScene &GameScene::operator=(GameScene &&other) noexcept {
  if (this == &other)
    return *this;
  nameScene = std::move(other.nameScene);
  level = std::move(other.level);
  time = std::move(other.time);
  background = std::move(other.background);
  camera = std::move(other.camera);
  player = std::move(other.player);
  gameOver = std::move(other.gameOver);
  entityFactory = std::move(other.entityFactory);
  entities = std::move(other.entities);
  lives = std::move(other.lives);
  systems = std::move(other.systems);
  update_systems = std::move(other.update_systems);
  draw_systems = std::move(other.draw_systems);
  return *this;
}
GameScene::GameScene(bool resume) : Scene(), EM(&EntityManager::getInstance()) {
  if (resume) {
    load();

    GameScene game = GameScene(nameScene, level);
    *this = std::move(game);
    EM = &EntityManager::getInstance();
  }
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
  if (!gameOver)
    save();
  EM->reset();
}
void GameScene::loadResources() {
  // Loading BackGround
  Image bImage = LoadImage(
      ("assets/" + nameScene + "/Background-" + level + ".png").c_str());
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  // Create Map
  entities = mapRenderer.createMap("assets/" + nameScene + "/" + nameScene +
                                   "-" + level + ".json");
}
void GameScene::draw() {
  float dt = GetFrameTime();
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);

  for (auto &system : draw_systems) {
    system.lock()->draw(dt);
  }

  EndMode2D();
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE,
           WHITE);
  DrawText(TextFormat("Lives: %03i", (int)lives), 1200 - 35 * 6, 35,
           GAMEPLAY_TEXT_SIZE, WHITE);
  DrawText(
      TextFormat("Score: %03i", (int)ScoreManager::getInstance().getScore()),
      1200 - 35 * 12, 35, GAMEPLAY_TEXT_SIZE, WHITE);
}
Unique<Scene> GameScene::updateScene(float deltaTime) {
  this->update(deltaTime);
  if (player.lock()->isActive() == false) {
    sleep(1);
    lives -= 1;
    if (lives == 0) {
      lives = 3;
      return make_unique<SceneSpace::IntroScene>();
    }
    return make_unique<SceneSpace::GameScene>(nameScene, level);
  } else if (player.lock()->hasComponent<PlayerTag>() == false &&
             player.lock()->getComponent<PositionComponent>().x >
                 164.0f * 16.0f) {
    if (level == "Easy") {
      return make_unique<SceneSpace::GameScene>(nameScene, "Medium");
    }
    if (level == "Medium") {
      return make_unique<SceneSpace::GameScene>(nameScene, "Hard");
    }
    return make_unique<SceneSpace::IntroScene>();
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

void GameScene::save() {
  string path = savePath + level + nameScene + ".txt";
  std::ofstream o(path);
  ASSERT(o.is_open(), "Failed to open file");
  o << lives << "\n";
  ScoreManager::getInstance().save(o);
  o << level << "\n";
  o << time << "\n";
  o << nameScene << "\n";
  o.close();
}

void GameScene::load() {
  string path = savePath + level + nameScene + ".txt";
  std::ifstream i(path);
  // ASSERT(i.is_open(), "Failed to open file");
  if (!i.is_open()) {
    throw 1;
  }
  i >> lives;
  ScoreManager::getInstance().load(i);
  i >> level;
  i >> time;
  i >> nameScene;
  i.close();
}
} // namespace SceneSpace
