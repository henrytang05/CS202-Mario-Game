#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"
#include "Entity/Mario.h"
#include "Entity/Luigi.h"
#include "pch.h"
#include <memory>
#include "TextureManager.h"
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
Shared<AbstractEntity> EntityFactory::createBlock(string type, Vector2 position) {
  Texture2D texture = TextureManager::getInstance().getTexture(type);
  std::cerr<<"Still good get into createBlock"<<std::endl; 
  Shared<AbstractEntity> block = nullptr;
  if(type == "NormalBlock"){
    block = std::make_shared<NormalBlock>(position);
  }
  else if(type == "BrokenBlock"){
    block = std::make_shared<BrokenBlock>(position);
  }
  else if(type == "HardBlock"){
    block = std::make_shared<HardBlock>(position);
  }
  else if(type == "GroundBlock"){
    block = std::make_shared<GroundBlock>(position);
  }
  else if(type == "QuestionBlock"){
    block = std::make_shared<QuestionBlock>(position);
  }
  return block;
}

Shared<AbstractEntity> EntityFactory::createPipe(Vector2 position, Vector2 size) {
  Shared<AbstractEntity> pipe = std::make_shared<Pipe>(position, size);
  return pipe;
}

Shared<AbstractEntity> EntityFactory::createFlag(Vector2 position)
{
  Shared<AbstractEntity> flag = std::make_shared<Flag>(position);
  return flag;
}

Shared<AbstractEntity> EntityFactory::createFlagPole(Vector2 position)
{
  Shared<AbstractEntity> flagPole = std::make_shared<FlagPole>(position);
  return flagPole;
}
