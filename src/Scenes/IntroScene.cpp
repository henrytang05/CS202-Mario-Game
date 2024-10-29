#include "Scenes/IntroScene.h"
#include "raylib.h"

IntroScene::IntroScene() : Scene() {}
IntroScene::~IntroScene() = default;

void IntroScene::Update() {
  DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
  DrawText("This is IntroScene", 190, 180, 20, LIGHTGRAY);
}
