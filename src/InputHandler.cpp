#include "InputHandler.h"
#include "raylib.h"
void InputHandler::inputHandleForGameScene(SceneSpace::GameScene &listener) {
    if(IsKeyDown(KEY_RIGHT)) listener.pressRight();
    else if(IsKeyDown(KEY_LEFT)) listener.pressLeft();
    else if(IsKeyPressed(KEY_UP)) listener.pressUp();
    else listener.pressNothing();
}

void InputHandler::inputHandleForIntroScene(SceneSpace::IntroScene &listener) {
}