#include "Scenes/Scene.h"
#include "Scenes/GameScene.h"
#include "Scenes/IntroScene.h"
#include "InputHandler.h"
#include "Logger.h"
#include "globals.h"
namespace SceneSpace {

GameScene::GameScene() : Scene() {
}
GameScene::~GameScene() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  characters = {make_shared<TextureSmallCharacter>("./assets/Luigi-Small")};
}
void GameScene::start() {
  gameOver = false; 
  velocity = {0, 0};
  ground = screenHeight - 48;
  position = {0, 784};//Uy change
  frameIndex = frameDelayCounter = 0;
  frameDelay = 10;
  gravity = 1;
}
void GameScene::acceptInputHandler(InputHandler inputHandler) {
  inputHandler.inputHandleForGameScene(*this);
}
void GameScene::draw() {
  characters[0]->drawTexture(position);
}
void GameScene::pressUp() {
  if(position.y >= ground) {
    velocity.y = -15;
  }
}
void GameScene::pressLeft() {
  if(position.y >= ground) {
    velocity.x = -2;
    if(!characters[0]->getIsFlip()) {
      characters[0]->updateFlip();
      characters[0]->updateFrame(frameIndex);
    }
  }
}
void GameScene::pressRight() {
  if(position.y >= ground) {
    velocity.x = 2;
    if(characters[0]->getIsFlip()) {
      characters[0]->updateFlip();
      characters[0]->updateFrame(frameIndex);
    }
  }
}
void GameScene::pressNothing() {
  if(position.y >= ground) {
    velocity.x = 0;
    frameIndex = 0;
  }
}
Shared<Scene> GameScene::update() {
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
    characters[0]->updateFrame(frameIndex);
  }
  return nullptr;
}

bool GameScene::isFinished() { return gameOver; }
Vector2 GameScene::getCameraTarget(){
  return position;
}
} // namespace SceneSpace
