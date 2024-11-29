#include "pch.h"

#include "Logger.h"
#include "Scenes/Scene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GameScene.h"
#include "InputHandler.h"
namespace SceneSpace {
IntroScene::IntroScene() : Scene() {}
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
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
  DrawText("This is IntroScene", 190, 180, 20, LIGHTGRAY);
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
