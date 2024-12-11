#include "Scenes/GameScene.h"

#include <memory>

#include "Components/Camera.h"
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

GameScene::GameScene() : Scene(), camera({0, 0}) { init(); }

void GameScene::init() {
  entityFactory = std::make_unique<EntityFactory>();
  Shared<Mario> mario = entityFactory->createMario();
  player = mario;
  entities.push_back(mario);

  gameOver = false;
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  camera.target.y = 784.0f - 186.0f;
  camera.zoom = 2.0f;
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  std::cerr<<"loadResources"<<endl;
  mapCollision.resize(100, std::vector<Shared<AbstractEntity>>(100, nullptr));
  mapRenderer = MapRenderer("Map/Level1.json", mapCollision);
}
void GameScene::draw() {
  BeginMode2D(camera);

  mapRenderer.render();
  player->draw();

  EndMode2D();
}
Shared<Scene> GameScene::updateScene() {
  this->update();
  //player->update();
  return nullptr;
}
void GameScene::update() {
  for (auto &entity : entities) {
    entity->update();
  }
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= screenWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth - screenWidth / (2.0f * camera.zoom);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
