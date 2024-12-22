// #include "Entity/Enemy.h"
// #include "Components/BoundingBox.h"
// #include "Components/Components_include.h"
// #include "Components/Position.h"
// #include "Components/Texture.h"
// #include "Components/Transform.h"
// #include "TextureManager.h"

// Enemy::Enemy(std::string name) : AbstractEntity(name) {}


// Goomba::Goomba(std::string name) : Enemy(name) {
//   Vector2 position = {0, 0}; // Set initial position
//   Vector2 size = {16, 16};
//   addComponent<PositionComponent>(position);
//   addComponent<BoundingBoxComponent>(size);
//   addComponent<TextureComponent>();
//   getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Goomba"));
// }

// void Goomba::update(float deltaTime) {
//   Enemy::update(deltaTime);
// }

// void Goomba::draw() {
//   Enemy::draw();
// }

// void Goomba::handleCollision() {
//   // Implement specific collision handling for Goomba
// }