#include "Entity/EntityFactory.h"

#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Rigid.h"
#include "Components/Transform.h"
#include "Entity/newCharacter.h"
#include "pch.h"

Shared<Entity> EntityFactory::createMario() {
  Shared<Entity> mario = std::make_shared<newCharacter>("Mario");

  Vector2 size({16, 23});
  Vector2 position = {0, (float)ground - size.y};
  Vector2 velocity = {0, 0};

  mario->addComponent<PositionComponent>(position);
  mario->addComponent<TransformComponent>(velocity, .1);
  mario->addComponent<BoundingBoxComponent>(size);
  mario->addComponent<RigidBodyComponent>();
  // mario->addComponent<CameraComponent>();
  mario->addComponent<TextureComponent>("./assets/Luigi-Small", 11);

  return mario;
}
Shared<Entity> EntityFactory::createLuigi() {
  Unique<Entity> luigi = std::make_unique<Entity>();
  // TODO: Add components
  return luigi;
}
Shared<Entity> EntityFactory::createGoomba() {
  Unique<Entity> goomba = std::make_unique<Entity>();
  // TODO: Add components
  return goomba;
}
