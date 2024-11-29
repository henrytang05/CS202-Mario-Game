#include "pch.h"

#include "Game.h"
#include "Logger.h"
#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"

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
    currentScene->acceptInputHandler(inputHandler);
    Shared<SceneSpace::Scene> nextScene = currentScene->update();
    if(nextScene) {
      currentScene = nextScene;
      currentScene->loadResources();
      currentScene->start();
    }
    // Draw
    BeginDrawing();
    currentScene->draw();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}
void Game::clean() { CloseWindow(); }
