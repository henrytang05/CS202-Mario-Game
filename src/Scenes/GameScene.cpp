#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Logger.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() 
    : Scene() {
}
GameScene::~GameScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}
void GameScene::loadResources() { 
      tileFactory = TileFactory("Map/OverWorld.json", "Map/OverWorld.png"); 
      mapRenderer = MapRenderer("Map/Level1.json", tileFactory);
}
void GameScene::start() {
  gameOver = false;
  player = make_shared<Character>("./assets/Luigi-Small", 11, Vector2{0.0f, 0.0f}, Vector2{16, 23});
  camera.offset = {screenWidth/2.0f, screenHeight/2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player->getPosition().x;
  camera.target.y = 784.0f-186.0f;
  camera.zoom = 2.0f;
}
void GameScene::draw() {
  BeginMode2D(camera);
  mapRenderer.Render();
  player->draw();
  EndMode2D();
}
Shared<Scene> GameScene::update() {
  player->update();
  camera.target.x = player->getPosition().x;
  if(camera.target.x <= screenWidth/(2.0f * camera.zoom))
    camera.target.x = screenWidth/(2.0f * camera.zoom);
  if(camera.target.x >= screenWidth - screenWidth/(2.0f * camera.zoom))
    camera.target.x = screenWidth - screenWidth/(2.0f * camera.zoom);
  return nullptr;
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
