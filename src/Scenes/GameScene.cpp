#include "Scenes/GameScene.h"
#include "Logger.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() : Scene() {
  gameOver = false; 
  velocity = {0, 0};
  position = {0, screenHeight/2};
  frameIndex = frameDelayCounter = 0;
  frameDelay = 5;
  characters = {make_shared<TextureSmallCharacter>("./assets/Luigi-Small")};
}
GameScene::~GameScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}

void GameScene::Update() {
  if(IsKeyDown(KEY_RIGHT)) {
    velocity.x = 2;
    if(characters[0]->getIsFlip()) {
      characters[0]->updateFlip();
      characters[0]->updateFrame(frameIndex);
    }
  }
  else if(IsKeyDown(KEY_LEFT)) {
    velocity.x = -2;
    if(!characters[0]->getIsFlip()) {
      characters[0]->updateFlip();
      characters[0]->updateFrame(frameIndex);
    }
  }
  else {
    velocity.x = 0;
    frameIndex = 0;
  }
  position.x += velocity.x;
  position.y += velocity.y;
  bool isMoving = ((velocity.x != 0)||(velocity.y != 0));
  frameDelayCounter += 1;
  if(frameDelayCounter > frameDelay) {
    frameDelayCounter = 0;
    if(isMoving) {
      frameIndex += 1;
      frameIndex %= 2;
    }
    characters[0]->updateFrame(frameIndex);
  }
  characters[0]->drawTexture(position);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
