#include "Entity/EntityFactory.h"

#include "Components/Components_include.h"
#include "Entity/Enemy.h"
#include "Entity/Mario.h"
#include "EntityManager.h"
#include "GameObject.h"
#include "pch.h"
#include "raylib.h"

EntityFactory::EntityFactory(EntityManager &EM) : IFactory(EM) {}
//
Weak<AbstractEntity> EntityFactory::createMario() { return initMario(); }
Weak<AbstractEntity> EntityFactory::createLuigi() { return initLuigi(); }
Weak<AbstractEntity> EntityFactory::createGoomba(Vector2 position,
                                                 Vector2 size) {
  return initGoomba(position, size);
}

Weak<AbstractEntity> EntityFactory::createKoopa(Vector2 position,
                                                Vector2 size) {
  return initKoopa(position, size);
}
//Create Piranha
Weak<AbstractEntity> EntityFactory::createPiranha(Vector2 position) {
  return initPiranha(position);
}

Weak<AbstractEntity> EntityFactory::createBlock(std::string type,
                                                Vector2 position) {
  Texture2D texture = TextureManager::getInstance().getTexture(type);

  std::cerr << "Still good get into createBlock" << std::endl;
  Weak<AbstractEntity> block;
  if (type == "NormalBlock") {
    block = createNormalBlock(position);
  } else if (type == "BrokenBlock") {
    block = createBrokenBlock(position);
  } else if (type == "HardBlock") {
    block = createHardBlock(position);
  } else if (type == "GroundBlock") {
    block = createGroundBlock(position);
  } else if (type == "QuestionBlock") {
    block = createQuestionBlock(position);
  } else {
    throw std::runtime_error("Block type not found");
  }
  return block;
}
Weak<Pipe> EntityFactory::createPipe(Vector2 position, Vector2 size) {
  Shared<Pipe> pipe = std::make_shared<Pipe>(position, size);
  return pipe;
}

Weak<Flag> EntityFactory::createFlag(Vector2 position) {
  Shared<Flag> flag = std::make_shared<Flag>(position);
  return flag;
}

Weak<FlagPole> EntityFactory::createFlagPole(Vector2 position) {
  Shared<FlagPole> flagPole = std::make_shared<FlagPole>(position);
  return flagPole;
}


Weak<AbstractEntity> EntityFactory::createMushroom(Vector2 position) {
  //initMushroom(position) is implmented below
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("Mushroom").lock();
  Vector2 size = {16,16};
  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("Mushroom"));
  entity->getComponent<TextureComponent>().addTexture("Left-Moving", TextureManager::getInstance().getTexture("Mushroom"));
  entity->getComponent<TextureComponent>().addTexture("Right-Moving", TextureManager::getInstance().getTexture("Mushroom"));
  entity->getComponent<TextureComponent>().addTexture("Die", TextureManager::getInstance().getTexture("Mushroom"));
  entity->getComponent<TextureComponent>().changeState("Normal");
  entity->addComponent<AITag>();
  entity->addComponent<PowerupTag>();
  entity->addComponent<CollisionComponent>();
  entity->addComponent<TransformComponent>(Vector2{50.0f, -16.0f});
  return entity;

}

