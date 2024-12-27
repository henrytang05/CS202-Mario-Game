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
  QuitButton = new GUI::ImageButton(30, 20, "./assets/QuitButton.png",
                                       "./assets/Hover_QuitButton.png");
  YES = new GUI::ImageButton(540, 485, "./assets/YES.png", "./assets/Hover_YES.png");
  NO = new GUI::ImageButton(750, 485, "./assets/NO.png", "./assets/Hover_NO.png");
  QuitGame = LoadTexture("./assets/QuitGame.png");
}

void Game::run() {
  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    update(deltaTime);
    draw();
  }
}

void Game::update(float deltaTime) {
  if(!scenes.empty()){
    if(typeid(*scenes.top()) == typeid(SceneSpace::GameScene)){\
      Shared<SceneSpace::Scene> scene = scenes.top()->updateScene(deltaTime);
      if(scene){
        popScene();
        pushScene(scene);
      }
    }
    else pushScene(scenes.top()->updateScene(deltaTime));    
    Vector2 mousePos = GetMousePosition();
    bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if(typeid(*scenes.top()) != typeid(SceneSpace::IntroScene)) {
      QuitButton->update(mousePos, isLeftClick);
      if (QuitButton->isPressed())
      {
        if(typeid(*scenes.top()) == typeid(SceneSpace::GameScene)){
          quittingGame = true;
        }
        else popScene();
      }
    }
    if(quittingGame){
      YES->update(mousePos, isLeftClick);
      NO->update(mousePos, isLeftClick);
      if(YES->isPressed()){
        quittingGame = false;
        popScene();
      }
      if(NO->isPressed()) quittingGame = false;
    } 
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
  if(typeid(*scenes.top()) != typeid(SceneSpace::IntroScene)) {
    QuitButton->draw();
  }
  if(quittingGame){
    DrawTexture(QuitGame, 420, 198, WHITE);
    YES->draw();
    NO->draw();
  }
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