#include "pch.h"

#include "Game.h"
#include "Logger.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/Scene.h"
#include "globals.h"

Game::Game() { init(); }
Game::~Game() {
  clean();
#ifdef _DEBUG
  Log("Game destroyed");
#endif
}

void Game::init() {
  InitWindow(screenWidth, screenHeight, "Super Mario");
  SetTargetFPS(60);
  currentScene = std::make_shared<SceneSpace::IntroScene>();
  currentScene->loadResources();
  currentScene->start();
}

void Game::run() {
  while (!WindowShouldClose()) {
    update();
    draw();
  }
}
void Game::update() {
  Shared<SceneSpace::Scene> nextScene = currentScene->updateScene();
  if (nextScene) {
    currentScene = nextScene;
    currentScene->loadResources();
    currentScene->start();
  }
}
void Game::clean() { CloseWindow(); }
void Game::draw() {
  BeginDrawing();
  currentScene->draw();
  EndDrawing();
}
