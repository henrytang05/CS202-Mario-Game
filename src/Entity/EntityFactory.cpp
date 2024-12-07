#include "Entity/EntityFactory.h"

#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Rigid.h"
#include "Components/Transform.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"
#include <memory>

Shared<Mario> EntityFactory::createMario() {
  Shared<Mario> mario = std::make_shared<Mario>();

  // Vector2 size({16, 23});
  // Vector2 position = {0, (float)ground - size.y};
  // Vector2 velocity = {0, 0};
  //
  // mario->addComponent<PositionComponent>(position);
  // mario->addComponent<TransformComponent>(velocity, .1);
  // mario->addComponent<BoundingBoxComponent>(size);
  // mario->addComponent<RigidBodyComponent>();
  // // mario->addComponent<CameraComponent>();
  // mario->addComponent<TextureComponent>("./assets/Luigi-Small", 11);

  return mario;
}
Shared<Entity> EntityFactory::createLuigi() {
  // Shared<Entity> luigi = std::make_shared<Entity>();
  // // TODO: Add components
  // return luigi;
  return nullptr;
}
Shared<Entity> EntityFactory::createGoomba() {
  // Shared<Entity> goomba = std::make_shared<Entity>();
  // // TODO: Add components
  // return goomba;
  return nullptr;
}
