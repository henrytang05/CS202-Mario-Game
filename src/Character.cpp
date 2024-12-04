#include "Character.h"
#include "CharacterState.h"
#include "Logger.h"
Character::Character(std::string filename, int _numFrame, Vector2 _size) : TextureCharacter(filename, _numFrame) {   
  velocity = {0, 0};
  ground = 3 * screenHeight / 4;
  position = {0, (float)ground};
  stateCharacter = new StandingState({0.0f, 0.0f});
  size = _size;
}
Character::~Character() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, "Character destroyed");
#endif
    delete stateCharacter;
}
void Character::update() {
    CharacterState *newState = stateCharacter->handleInput(*this);
    if(newState) {
        delete stateCharacter;
        stateCharacter = newState;
    }
    stateCharacter->update(*this);
    position.x += velocity.x;
    position.y += velocity.y;
    if(position.x <= 0) position.x = 0.0f;
    if(position.x + size.x >= screenWidth) position.x = screenWidth - size.x;
    if(position.y >= ground) position.y = ground;
}
void Character::draw() {
    drawTexture(position);
}
void Character::setVelocity(Vector2 newVelocity) {
    velocity = newVelocity;
}
Vector2 Character::getVelocity() {
    return velocity;
}
bool Character::isOnTheGround() {
    return (position.y >= ground);
}