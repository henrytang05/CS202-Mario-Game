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

GameScene::GameScene() : Scene(), camera({0, 0}) {

}
 
void GameScene::init() {
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
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  //Loading BackGround
  Image bImage = LoadImage("Map/BackGroundnew.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  //Create Map
  entities = mapRenderer.createMap("Map/level1.json");
}
void GameScene::draw() {
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);
  for (auto &entity : entities) {
    if(entity!=nullptr)
    entity->draw();
  }

  EndMode2D();
}
Shared<Scene> GameScene::updateScene() {
  this->update();
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
  SoundCtrl.Update();
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
