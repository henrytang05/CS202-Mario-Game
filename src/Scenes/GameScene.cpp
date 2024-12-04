#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Logger.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() : Scene() {
}
GameScene::~GameScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}
void GameScene::loadResources() {
}
void GameScene::start() {
  gameOver = false;
  characters = {make_shared<Character>("./assets/Luigi-Small", 11)};
}
void GameScene::draw() {
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
