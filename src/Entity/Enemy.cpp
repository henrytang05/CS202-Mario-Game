// #include "Entity/Enemy.h"
// Piranha::Piranha(Vector2 position) {
//   addComponent<PositionComponent>(position);
//   addComponent<BoundingBoxComponent>(position, 16, 32);
//   addComponent<TextureComponent>();
//   getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Piranha"));
// }

// void Piranha::update(float deltaTime) {
//   // Implement specific update logic for Piranha
//   auto pos = getComponent<PositionComponent>().getPosition();
//   // Example movement logic
//   pos.y += ENEMY_SPEED * deltaTime;
//   getComponent<PositionComponent>().setPosition(pos);
// }

// void Piranha::draw() {
//   ASSERT(hasComponent<TextureComponent>());
//   getComponent<TextureComponent>().drawTexture("Normal");
// }
// void Piranha::handleCollision() {
//   // Implement specific collision logic for Piranha
// }