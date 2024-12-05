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
  // b2Vec2 gravity(0.0f, -9.8f); // Gravity vector
  // b2World world(gravity);
  // TileFactory factory("Map/OverWorld.json", "Map/OverWorld.png");
  // MapRenderer mapRenderer("Map/Level1.json", factory);
  while (!WindowShouldClose()) {
    currentScene->acceptInputHandler(inputHandler);
    Shared<SceneSpace::Scene> nextScene = currentScene->update();
    if(nextScene) {
      currentScene = nextScene;
      currentScene->loadResources();
      currentScene->start();
    }
  //   MyCamera camera;
  //  // Dynamic cast to GameScene to get the camera target
  //       auto gameScene = std::dynamic_pointer_cast<SceneSpace::GameScene>(currentScene);
        
    // Draw
        BeginDrawing();
        ClearBackground({185,246,250,0});//Uy change
        // if (gameScene) {
        //   camera.Update(gameScene->getCameraTarget());
        // }
        //camera.BeginMode();
        //mapRenderer.Render();
        currentScene->draw();
        //camera.EndMode();

        EndDrawing();
  }
}
void Game::clean() { CloseWindow(); }
