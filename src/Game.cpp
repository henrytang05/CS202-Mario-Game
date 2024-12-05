#include "pch.h"

#include "Game.h"
#include "Logger.h"
#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Map.h"
Game::Game() { init(); }
Game::~Game() {
  clean();
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "Game destroyed");
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
    Shared<SceneSpace::Scene> nextScene = currentScene->update();
    if(nextScene) {
      currentScene = nextScene;
      currentScene->loadResources();
      currentScene->start();
    }
    // Draw
    BeginDrawing();
    currentScene->draw();
    EndDrawing();
  }
}
void Game::clean() { CloseWindow(); }
