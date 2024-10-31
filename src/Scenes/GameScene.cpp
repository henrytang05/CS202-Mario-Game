#include "Scenes/GameScene.h"
#include "Logger.h"

namespace SceneSpace {

GameScene::GameScene() : Scene() {}
GameScene::~GameScene() {
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
}

void GameScene::Update() {
  DrawText("Welcome to GameScene", 190, 200, 20, LIGHTGRAY);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
