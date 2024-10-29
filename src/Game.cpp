#include "Game.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "pch.h"

Game::Game() { Init(); }

void Game::Init() {
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  currentScene = std::make_unique<IntroScene>();
}

void Game::Run() {
  while (!WindowShouldClose()) { // Detect window close button or ESC key
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Update();
    EndDrawing();
  }
  Clean();
}

void Game::Update() {
  if (IsKeyPressed(KEY_ENTER)) {
    if (dynamic_cast<IntroScene *>(currentScene.get())) {
      currentScene = std::make_unique<GameScene>();
    } else
      currentScene = std::make_unique<IntroScene>();
  }
  currentScene->Update();
}
void Game::Clean() { CloseWindow(); }
