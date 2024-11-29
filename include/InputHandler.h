#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "Scenes/Scene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GameScene.h"
class InputHandler {
public:
    void inputHandleForGameScene(SceneSpace::GameScene &listener);
    void inputHandleForIntroScene(SceneSpace::IntroScene &listener);
};
#endif // INPUTHANDLER_H