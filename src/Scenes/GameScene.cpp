#include "Scenes/GameScene.h"
#include "Logger.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() : Scene() {
  gameOver = false; 
  velocity = {0, 0};
  ground = 3 * screenHeight / 4;
  position = {0, (float)ground};
  frameIndex = frameDelayCounter = 0;
  frameDelay = 10;
  gravity = 1;
  characters = {make_shared<TextureSmallCharacter>("./assets/Luigi-Small")};
}
GameScene::~GameScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}

void GameScene::Update() {
  bool isDuckling = 0;
  if(position.y >= ground) {
    if( IsKeyDown(KEY_UP)) {
      velocity.y = -15;
    }
    else if(IsKeyDown(KEY_RIGHT)) {
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
      if(IsKeyDown(KEY_DOWN)) {
        isDuckling = true;
      }
    }
  }
  position.x += velocity.x;
  position.y += velocity.y;
  bool isOnTheGround = (position.y >= ground);
  if(isOnTheGround) {
    velocity.y = 0;
    position.y = ground;  
  }
  else {
    velocity.y += gravity;
  }
  bool isMoving = ((velocity.x != 0)||(velocity.y != 0));
  frameDelayCounter += 1;
  if(frameDelayCounter > frameDelay) {
    frameDelayCounter = 0;
    if(isMoving) {
      if(isOnTheGround) {
        frameIndex += 1;
        frameIndex %= 2;
      }
      else {
        if(velocity.y < 0) {
          frameIndex = 4;
        }
        else {
          frameIndex = 5;
        }
      }
    }
    else if(isDuckling) {
      frameIndex = 8;
    }
    characters[0]->updateFrame(frameIndex);
  }
  characters[0]->drawTexture(position);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
