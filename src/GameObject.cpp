#include "GameObject.h"

#include "Components/BlockTrigger.h"
#include "Components/Component.h"
#include "Components/Components_include.h"
#include "EntityManager.h"
Weak<AbstractEntity> createGroundBlock(Vector2 position) {
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("GroundBlock").lock();

  Vector2 size({16, 16});
  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<TextureComponent>();
  entity->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("GroundBlock"));

  return entity;
}

Weak<AbstractEntity> createBrokenBlock(Vector2 position) {
  Vector2 size({16, 16});
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("BrokenBlock").lock();
  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<BlockTriggerComponent>();
  entity->addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
  entity->addComponent<TextureComponent>();
  entity->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("BrokenBlock"));
  return entity;
}

Weak<AbstractEntity> createHardBlock(Vector2 position) {
  Vector2 size({16, 16});
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("HardBlock").lock();

  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<TextureComponent>();
  entity->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("HardBlock"));

  return entity;
}
Weak<AbstractEntity> createNormalBlock(Vector2 position) {
  Vector2 size({16, 16});
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("NormalBlock").lock();

  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<TextureComponent>();
  entity->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("NormalBlock"));

  return entity;
}
Weak<AbstractEntity> createQuestionBlock(Vector2 position) {
  Vector2 size({16, 16});
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("QuestionBlock").lock();
  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<BlockTriggerComponent>();
  entity->addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
  entity->addComponent<TextureComponent>();
  entity->getComponent<TextureComponent>().addTexture("Normal", TextureManager::getInstance().getTexture("QuestionBlock"));
  return entity;
}
Pipe::Pipe(Vector2 position, Vector2 size) : AbstractEntity("Pipe") {
  initEntity();
  init(position, {32, 128});
}

void Pipe::init(Vector2 position, Vector2 size) {
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("Pipe"));
  std::cerr << "create pipe" << std::endl;
}
// void Pipe::draw() {
//   // ASSERT(hasComponent<TextureComponent>());
//   // getComponent<TextureComponent>().drawTexture("Normal");
// }
//
// void Pipe::update(float deltaTime) {}

//
Flag::Flag(Vector2 position) : AbstractEntity("Flag") {
  initEntity();
  init(position);
}

void Flag::init(Vector2 position) {
  Vector2 size = {16, 16};
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("Flag"));
}

// void Flag::draw() {
//   ASSERT(hasComponent<TextureComponent>());
//   getComponent<TextureComponent>().drawTexture("Normal");
// }

// void Flag::update(float deltaTime) {}

FlagPole::FlagPole(Vector2 position) : AbstractEntity("FlagPole") {
  initEntity();
  init(position);
  std::cerr << "create flagpole" << std::endl;
}

void FlagPole::init(Vector2 position) {
  Vector2 size = {16, 16};
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("FlagPole"));
}

// void FlagPole::draw() {
//   ASSERT(hasComponent<TextureComponent>());
//   getComponent<TextureComponent>().drawTexture("Normal");
// }
//
// void FlagPole::update(float deltaTime) {}

Piranha::Piranha(Vector2 position) : AbstractEntity("Piranha") {
  initEntity();
  Vector2 size = {16, 32};
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  std::vector<Texture2D> textures;
  textures.push_back(TextureManager::getInstance().getTexture("Piranha1"));
  textures.push_back(TextureManager::getInstance().getTexture("Piranha2"));
  getComponent<TextureComponent>().addTexture("Normal", textures, 0.1f, true);
  getComponent<TextureComponent>().changeState("Normal");
  addComponent<EnemyTag>();
  addComponent<SwingComponent>(position, 0);
}

Mushroom::Mushroom(Vector2 position) {
  initEntity();
  Vector2 size = {0, 0};
  addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
  addComponent<BoundingBoxComponent>(size);
  addComponent<PositionComponent>(position);
  position_fixed = getComponent<PositionComponent>().getPosition();
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("Mushroom"));
}

void Mushroom::update(float deltaTime) {
  if (isTriggered) {
    elapsedTime += deltaTime;

    auto position_change = getComponent<PositionComponent>().getPosition();
    position_change.y = position_change.y - 16.0f * deltaTime;

    // Ensure it doesn't go below the fixed position
    if (position_change.y < position_fixed.y - 16.0f) {
      position_change.y = position_fixed.y - 17.0f;
      isTriggered = false;
      getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 16.0f});
      getComponent<TransformComponent>().setVelocity((Vector2){50.0f, 10.0f});

      addComponent<CollisionComponent>();
    }
    getComponent<PositionComponent>().setPosition(position_change);
  }
}

void Mushroom::onNotify() { isTriggered = true; }
