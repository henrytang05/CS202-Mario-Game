#include "Scenes/GameScene.h"

GameScene::GameScene() : Scene() {}
GameScene::~GameScene() = default;

void GameScene::Update() {
  DrawText("Welcome to GameScene", 190, 200, 20, LIGHTGRAY);
}

bool GameScene::isFinished() { return gameOver; }
