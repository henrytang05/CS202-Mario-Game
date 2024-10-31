#include "Game.h"

#include "Logger.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/Scene.h"
#include "pch.h"

Game::Game() { Init(); }
Game::~Game() {
  Clean();
  Log("log.txt", LogLevel::INFO, "Game destroyed");
}

void Game::Init() {
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);
  m_scenes.insert({SceneType::INTRO, std::make_shared<IntroScene>()});
  m_scenes.insert({SceneType::GAME, std::make_shared<GameScene>()});
  m_currentSceneType = SceneType::INTRO;
  m_currentScene = m_scenes[m_currentSceneType];
}

void Game::Run() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Update();
    EndDrawing();
  }
}

void Game::Update() {
  if (IsKeyPressed(KEY_ENTER)) {
    if (m_currentSceneType == SceneType::INTRO) {
      m_currentSceneType = SceneType::GAME;
    } else {
      m_currentSceneType = SceneType::INTRO;
    }
    m_currentScene = m_scenes[m_currentSceneType];
  }

  m_currentScene.lock()->Update();
}
void Game::Clean() { CloseWindow(); }
