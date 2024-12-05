#include "Entity/EntityFactory.h"

#include "Components/BoundingBox.h"
#include "Components/Components.h"
#include "Components/Position.h"
#include "Components/Rigid.h"
#include "Components/Transform.h"
#include "Entity/newCharacter.h"
#include "pch.h"

Shared<Entity> EntityFactory::createMario() {
  Shared<Entity> mario = std::make_shared<newCharacter>("Mario");
  mario->addComponent<PositionComponent>();
  Vector2 pos = {1, 0};
  mario->addComponent<TransformComponent>(pos, 2);
  mario->addComponent<BoundingBoxComponent>();
  mario->addComponent<RigidBodyComponent>();
  mario->getComponent<BoundingBoxComponent>().setSize({16, 23});
  mario->addComponent<CameraComponent>();
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
