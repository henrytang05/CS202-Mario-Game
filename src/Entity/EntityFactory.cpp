#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"
#include <memory>

Shared<Mario> EntityFactory::createMario() {
  Shared<Mario> mario = std::make_shared<Mario>();

  return mario;
}
Shared<AbstractEntity> EntityFactory::createLuigi() {
  // Shared<Entity> luigi = std::make_shared<Entity>();
  // // TODO: Add components
  // return luigi;
  return nullptr;
}
Shared<AbstractEntity> EntityFactory::createGoomba() {
  // Shared<Entity> goomba = std::make_shared<Entity>();
  // // TODO: Add components
  // return goomba;
  return nullptr;
}
Shared<AbstractEntity> EntityFactory::createBlock(string type,Texture2D texture, Vector2 position) {
  if(type == "NormalBlock"){
    return std::make_shared<NormalBlock>(texture, position);
  }
  else if(type == "BrokenBlock"){
    return std::make_shared<BrokenBlock>(texture, position);
  }
  else if(type == "HardBlock"){
    return std::make_shared<HardBlock>(texture, position);
  }
  else if(type == "GroundBlock"){
    return std::make_shared<GroundBlock>(texture, position);
  }
  else if(type == "QuestionBlock"){
    return std::make_shared<QuestionBlock>(texture, position);
  }
}
