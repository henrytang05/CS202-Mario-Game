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
  characters = {make_shared<Character>("./assets/Luigi-Small", 11, Vector2{0.0f, 0.0f}, Vector2{16, 23})};
}
void GameScene::draw() {
  mapRenderer.Render();
  for(Shared<Character> ch : characters) {
    ch->draw();
  }
}
Shared<Scene> GameScene::update() {
  for(Shared<Character> ch : characters) {
    ch->update();
  }
  return nullptr;
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
