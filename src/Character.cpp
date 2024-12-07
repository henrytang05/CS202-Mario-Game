// #include "Character.h"
// #include "CharacterState.h"
// #include "Logger.h"
// Character::Character(std::string filename, int _numFrame, Vector2 _size)
//     : TextureCharacter(filename, _numFrame) {
//   velocity = {0, 0};
//   position = {0, (float)ground - size.y};
//   stateCharacter = new StandingState({0.0f, 0.0f});
//   size = _size;
//   camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
//   camera.rotation = 0.0f;
//   camera.target = position;
//   camera.zoom = 2.0f;
// }
// Character::~Character() {
// #ifdef _DEBUG
//   Log("log.txt", LogLevel::INFO, "Character destroyed");
// #endif
//   delete stateCharacter;
// }
// void Character::update() {
//   CharacterState *newState = stateCharacter->handleInput(*this);
//   if (newState) {
//     delete stateCharacter;
//     stateCharacter = newState;
//   }
//   stateCharacter->update(*this);
//   position.x += velocity.x;
//   position.y += velocity.y;
//   if (position.x <= 0)
//     position.x = 0.0f;
//   if (position.x + size.x >= screenWidth)
//     position.x = screenWidth - size.x;
//   if (position.y + size.y >= ground)
//     position.y = ground - size.y;
//   camera.target = position;
// }
// void Character::draw() {
//   BeginMode2D(camera);
//   drawTexture(position);
//   DrawLine(0.0f, ground, screenWidth, ground, BLACK);
//   ClearBackground(RAYWHITE);
//   EndMode2D();
// }
// void Character::setVelocity(Vector2 newVelocity) { velocity = newVelocity; }
// Vector2 Character::getVelocity() { return velocity; }
// bool Character::isOnTheGround() { return (position.y + size.y >= ground); }
