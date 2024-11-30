#include "pch.h"
#include "Logger.h"
#include "Scenes/Scene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GameScene.h"
#include "InputHandler.h"
namespace SceneSpace {
IntroScene::IntroScene() : Scene() {
  changeScreen = false;
  background = LoadTexture("./assets/MenuBackground.png");
}
IntroScene::~IntroScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "IntroScene destroyed");
#endif
}

Shared<Scene> IntroScene::update() {
  if(changeScreen)
    return std::make_shared<SceneSpace::GameScene>();
  return nullptr;
}
void IntroScene::draw() {
  DrawTexture(background,0,0,WHITE);
}
void IntroScene::pressEnter() {
  changeScreen = true;
}
void IntroScene::acceptInputHandler(InputHandler inputHandler) {
  inputHandler.inputHandleForIntroScene(*this);
}
void IntroScene::loadResources() {};
void IntroScene::start() {
  changeScreen = false;
};
} // namespace SceneSpace
