#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"
#include <memory>

Shared<Mario> EntityFactory::createMario() {
  Shared<Mario> mario = std::make_shared<Mario>();

  return mario;
}
Shared<Luigi> EntityFactory::createLuigi() {
  Shared<Luigi> luigi = std::make_shared<Luigi>();
  return luigi;
}
Shared<AbstractEntity> EntityFactory::createGoomba() {
  // Shared<Entity> goomba = std::make_shared<Entity>();
  // // TODO: Add components
  // return goomba;
  return nullptr;
}
