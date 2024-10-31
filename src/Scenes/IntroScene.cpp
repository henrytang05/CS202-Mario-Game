#include "Scenes/IntroScene.h"
#include "Logger.h"
#include "raylib.h"

namespace SceneSpace {
IntroScene::IntroScene() : Scene() {}
IntroScene::~IntroScene() {
  Log("log.txt", LogLevel::INFO, "IntroScene destroyed");
}

void IntroScene::Update() {
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
  DrawText("This is IntroScene", 190, 180, 20, LIGHTGRAY);
}
} // namespace SceneSpace
