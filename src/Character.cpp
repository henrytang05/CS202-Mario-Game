#include "Character.h"
#include "CharacterState.h"
#include "Logger.h"
Character::Character(std::string filename, int _numFrame, Vector2 _position, Vector2 _size) : TextureCharacter(filename, _numFrame), AABB(_position, _size) {   
    velocity = {0, 0};
    position = _position;
    size = _size;
    stateCharacter = new DroppingState({0.0f, 1.0f});
    camera.offset = {screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.target = position;
    camera.zoom = 2.0f;
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
    setPosition(position);
    if(checkCollision(boundLeft)) position.x = 0.0f;
    if(checkCollision(boundRight)) position.x = screenWidth - size.x;
    if(checkCollision(ground)) position.y = ground.getPosition().y - size.y;
    setPosition(position);
    camera.target = position;
}
void Character::draw() {
    //BeginMode2D(camera);
    drawTexture(position);
    DrawLine(ground.getPosition().x, ground.getPosition().y, ground.getPosition().x + screenWidth, ground.getPosition().y, BLACK);
    ClearBackground(RAYWHITE);
    //EndMode2D();
}
void Character::setVelocity(Vector2 newVelocity) {
    velocity = newVelocity;
}
Vector2 Character::getVelocity() {
    return velocity;
}
bool Character::isOnTheGround() {
    return checkCollision(ground);
}