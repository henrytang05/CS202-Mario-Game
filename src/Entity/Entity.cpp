#include "Entity/Entity.h"

#include "Logger.h"
#include "globals.h"

Entity::Entity() : name("Unnamed") { init(); }
Entity::Entity(std::string name) : name(name) {
#ifdef _DEBUG
  Log("log.txt", LogLevel::DEBUG, name + " created");
#endif
}

Entity::~Entity() {
#ifdef _DEBUG
  Log("log.txt", LogLevel::DEBUG, name + " destroy");
#endif
}

// void Entity::update() {
//   for (auto &c : components) {
//     c->update();
//   }
// }
//
// void Entity::draw() {
//   ASSERT(hasComponent<PositionComponent>());
//   // ASSERT(hasComponent<CameraComponent>());
//   ASSERT(hasComponent<TextureComponent>());
//   // PositionComponent &positionC = getComponent<PositionComponent>();
//   // Vector2 position = positionC.getPos();
//   // CameraComponent &camera = getComponent<CameraComponent>();
//
//   // BeginMode2D(camera);
//   // getComponent<TextureComponent>().drawTexture(position);
//   // DrawLine(0.0f, ground, screenWidth, ground, BLACK);
//   // ClearBackground(RAYWHITE);
//   // EndMode2D();
// }
