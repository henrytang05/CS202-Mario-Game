#include "GameObject.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"

#include "Components/BlockTrigger.h"
#include "EntityManager.h"

NormalBlock::NormalBlock(Vector2 position, EntityManager *EM)
    : AbstractEntity("NormalBlock") {
  if (EM) {
    initEntity(EM);
    init(position);

    return;
  }
}

void NormalBlock::init(Vector2 position) {
  Vector2 size({16, 16});
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("NormalBlock"));
}

void NormalBlock::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void NormalBlock::update(float deltaTime) {}

BrokenBlock::BrokenBlock(Vector2 position, EntityManager *EM)
    : AbstractEntity("BrokenBlock") {
  if (EM) {
    initEntity(EM);
    init(position);

    return;
  }
}

void BrokenBlock::init(Vector2 position) {
  Vector2 size({16, 16});
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<BlockTriggerComponent>();
  addComponent<TransformComponent>((Vector2){0.0f, 0.0f});
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("BrokenBlock"));
}

void BrokenBlock::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void BrokenBlock::update(float deltaTime) {}

HardBlock::HardBlock(Vector2 position, EntityManager *EM)
    : AbstractEntity("HardBlock") {
  if (EM) {
    initEntity(EM);
    init(position);
    return;
  }
}

void HardBlock::init(Vector2 position) {
  Vector2 size({16, 16});
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("HardBlock"));
}

void HardBlock::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void HardBlock::update(float deltaTime) {}

GroundBlock::GroundBlock(Vector2 position, EntityManager *EM)
    : AbstractEntity("GroundBlock") {
  if (EM) {
    initEntity(EM);
    init(position);
    return;
  }
}

void GroundBlock::init(Vector2 position) {
  Vector2 size({16, 16});
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("GroundBlock"));
}

void GroundBlock::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void GroundBlock::update(float deltaTime) {}

QuestionBlock::QuestionBlock(Vector2 position, EntityManager *EM)
    : AbstractEntity("QuestionBlock") {
  if (EM) {
    initEntity(EM);
    init(position);
    return;
  }
}

void QuestionBlock::init(Vector2 position) {
  Vector2 size({16, 16});
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("QuestionBlock"));
}

void QuestionBlock::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void QuestionBlock::update(float deltaTime) {}

Pipe::Pipe(Vector2 position, Vector2 size, EntityManager *EM)
    : AbstractEntity("Pipe") {
  if (EM) {
    initEntity(EM);
    init(position, size);
    return;
  }
}

void Pipe::init(Vector2 position, Vector2 size) {
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  std::cerr << "create pipe" << std::endl;
}
void Pipe::draw() {
  // ASSERT(hasComponent<TextureComponent>());
  // getComponent<TextureComponent>().drawTexture("Normal");
}

void Pipe::update(float deltaTime) {}

//
Flag::Flag(Vector2 position, EntityManager *EM) : AbstractEntity("Flag") {
  if (EM) {
    initEntity(EM);
    init(position);
    return;
  }
}

void Flag::init(Vector2 position) {
  Vector2 size = {16, 16};
  addComponent<PositionComponent>(position);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  getComponent<TextureComponent>().addTexture(
      "Normal", TextureManager::getInstance().getTexture("Flag"));
}

void Flag::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void Flag::update(float deltaTime) {}

FlagPole::FlagPole(Vector2 position, EntityManager *EM)
    : AbstractEntity("FlagPole") {
  if (EM) {
    initEntity(EM);
    init(position);

    return;
  }
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

void FlagPole::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture("Normal");
}

void FlagPole::update(float deltaTime) {}
