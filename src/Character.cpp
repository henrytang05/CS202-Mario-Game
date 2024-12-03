#include "Character.h"
Character::Character(std::string filename, int _numFrame) : TextureCharacter(filename, _numFrame) {   
  velocity = {0, 0};
  ground = 3 * screenHeight / 4;
  position = {0, (float)ground};
  gravity = 1;
  characterState = STATE_STANDING;
  delayFrame = 10;
  delayFrameCounter = 0;
}
void Character::update() {
    float dt = GetFrameTime();
    switch(characterState) {
        case STATE_STANDING:
        // Stopping acceleration
        if(velocity.x < 0) velocity.x = std::min(velocity.x + 1.0f, 0.0f);
        if(velocity.x > 0) velocity.x = std::max(velocity.x - 1.0f, 0.0f);
        if(IsKeyDown(KEY_UP)) {
            characterState = STATE_JUMPING;
        }
        else if(IsKeyDown(KEY_LEFT)) {
            characterState = STATE_MOVING;
        }
        else if(IsKeyDown(KEY_RIGHT)) {
            characterState = STATE_MOVING;
        }
        break;
        case STATE_MOVING:
        // Moving acceleration
        if(IsKeyDown(KEY_LEFT)) {
            velocity.x -= 0.5;
        }
        // Moving acceleration
        if(IsKeyDown(KEY_RIGHT)) {
            velocity.x += 0.5;
        }
        // User wants to stop
        if(IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)) {
            characterState = STATE_STANDING;
        }
        // User wants to jump
        if(IsKeyDown(KEY_UP)) {
            characterState = STATE_JUMPING;
        }
        break;
        case STATE_JUMPING:
        // Jumping acceleration in horizontal
        if(velocity.x < 0) velocity.x = std::min(velocity.x + 0.3f, 0.0f);
        if(velocity.x > 0) velocity.x = std::max(velocity.x - 0.3f, 0.0f);
        // Jumping acceleration in vertical
        if(IsKeyDown(KEY_UP)) {
            velocity.y = std::max(velocity.y - 2.0f, -15.0f);
        }
        // Time to drop
        if(IsKeyReleased(KEY_UP) || velocity.y <= -15.0f) {
            characterState = STATE_DROPPING;
        }
        break;
        case STATE_DROPPING:
        // Dropping acceleration in horizontal
        if(velocity.x < 0) velocity.x = std::min(velocity.x + 0.1f, 0.0f);
        if(velocity.x > 0) velocity.x = std::max(velocity.x - 0.1f, 0.0f);
        // Dropping acceleration in vertical
        velocity.y += gravity;
        // Post dropping
        if(position.y >= ground) {
            characterState = STATE_STANDING;
        }
    }
    velocity.x = std::min(velocity.x, 10.0f);
    velocity.x = std::max(velocity.x, -10.0f);
    position.x += velocity.x;
    position.y += velocity.y;
    bool isOnTheGround = (position.y >= ground);
    if(velocity.x < 0 && this->getIsFlip() == false) {
        this->updateFlip();
        this->updateFrame(frameIndex);
    }
    if(velocity.x > 0 && this->getIsFlip() == true) {
        this->updateFlip();
        this->updateFrame(frameIndex);
    }
    if(isOnTheGround) {
        velocity.y = 0;
        position.y = ground;  
    }
    ++delayFrameCounter;
    if(delayFrameCounter >= delayFrame) {
        delayFrameCounter = 0;
        if(characterState == STATE_MOVING) {
            frameIndex += 1;
            frameIndex %= 2;
        }
        if(characterState == STATE_JUMPING) {
            frameIndex = 4;
        }
        if(characterState == STATE_DROPPING) {
            frameIndex = 5;
        }
    }
    if(characterState == STATE_STANDING) {
        delayFrameCounter = 0;
        frameIndex = 0;
    }
    this->updateFrame(frameIndex);
}
void Character::draw() {
    drawTexture(position);
}