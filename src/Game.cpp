#include "Game.h"
#include "Interface.h"
#include "Logger.h"
#include "Map.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/Scene.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"

Game::Game() { init(); }
Game::~Game() {
  clean();
#ifdef _DEBUG
  Log("Game destroyed");
#endif
}

void Game::init() {
  InitWindow(screenWidth, screenHeight, "Super Mario");
  InitAudioDevice();
  SetTargetFPS(60);
  pushScene(std::make_unique<SceneSpace::IntroScene>());
  QuitButton = new GUI::ImageButton(30, 200, "./assets/QuitButton.png",
                                       "./assets/Hover_QuitButton.png");
}

void Game::run() {
  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    update(deltaTime);
    draw();
  }
}
void Game::update(float deltaTime) {
  pushScene(scenes.top()->updateScene(deltaTime));
  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  QuitButton->update(mousePos, isLeftClick);
  if (QuitButton->isPressed())
  {
    popScene();
    scenes.top()->setEnd(false);
  }
}
void Game::clean() {
  delete QuitButton;
  clearScene();
  CloseAudioDevice();
  CloseWindow();
}
void Game::draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  scenes.top()->draw();
  QuitButton->draw();
  EndDrawing();
}

void Game::pushScene(Shared<SceneSpace::Scene> scene)
{
  if(scene){
    scene->loadResources();
    scene->init();
    scenes.push(scene);
  }
}

void Game::popScene()
{
  if(!scenes.empty()){
    scenes.pop();
  }
  
}

void Game::clearScene()
{
  while(!scenes.empty()){
    scenes.pop();
  }
}
