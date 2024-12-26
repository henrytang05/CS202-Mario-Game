#include "Components/BlockTrigger.h"

#include "Components/Components_include.h"
#include "EntityManager.h"
#include "Entity/EntityFactory.h"
#include "GameObject.h"
using namespace std;

// BlockTriggerComponent
BlockTriggerComponent::BlockTriggerComponent()
    : Component("BlockTriggerComponent"), trigger(nullptr) {}
BlockTriggerComponent::~BlockTriggerComponent() {
  if (trigger) {
    delete trigger;
    trigger = nullptr;
  }
}
void BlockTriggerComponent::init() {}
void BlockTriggerComponent::setTrigger(TriggerBehaviour *_trigger) {
  if (trigger) {
    delete _trigger;
    _trigger = nullptr;
    return;
  }
  trigger = _trigger;
}
void BlockTriggerComponent::update(float deltaTime) {
  if (trigger) {
    EntityManager &EM = EntityManager::getInstance();
    auto entity = EM.getEntityRef(this->entity->getID());
    TriggerBehaviour *ptr = trigger->trigger(&entity, deltaTime);
    if (ptr == nullptr) {
      delete trigger;
      trigger = nullptr;
    }
  }
}

// TriggerBehaviour

// BrokenBlock
TriggerBrokenBlockWhenHitBySmall::TriggerBrokenBlockWhenHitBySmall() {
  sumFrame = 0.0f;
}

TriggerBrokenBlockWhenHitBySmall::TriggerBrokenBlockWhenHitBySmall(
    Vector2 _fixedPosition) {
  fixedPosition = _fixedPosition;
  sumFrame = 0.0f;
}

TriggerBehaviour *
TriggerBrokenBlockWhenHitBySmall::trigger(AbstractEntity *entity,
                                          float deltaTime) {
  TriggerBehaviour *retVal = this;
  sumFrame += deltaTime;
  Vector2 velocity = entity->getComponent<TransformComponent>().getVelocity();
  if (sumFrame < 0.1f) {
    velocity = velocity + (Vector2){0.0f, -600.0f * deltaTime};
  }
  velocity = velocity + (Vector2){0.0f, 240.0f * deltaTime};
  if (velocity.y >= 600.0f)
    velocity.y = 600.0f;
  if (velocity.y <= -600.0f)
    velocity.y = -600.0f;
  if (sumFrame >= 0.3f) {
    entity->getComponent<PositionComponent>().setPosition(fixedPosition);
    velocity.y = 0.0f;
    retVal = nullptr;
  }
  entity->getComponent<TransformComponent>().setVelocity(velocity);
  return retVal;
}

TriggerBrokenBlockWhenHitByLarge::TriggerBrokenBlockWhenHitByLarge() {
  sumFrame = 0.0f;
}

TriggerBrokenBlockWhenHitByLarge::TriggerBrokenBlockWhenHitByLarge(
    Vector2 _fixedPosition) {
  fixedPosition = _fixedPosition;
  sumFrame = 0.0f;
}

TriggerBehaviour *
TriggerBrokenBlockWhenHitByLarge::trigger(AbstractEntity *entity,
                                          float deltaTime) {
  TriggerBehaviour *retVal = this;
  sumFrame += deltaTime;
  if (sumFrame <= 0.1f) {
    entity->modifyComponent<TextureComponent>();
    vector<Texture2D> textures;
    textures.push_back(
        LoadTextureFromImage(LoadImage("assets/Block/Pieces1.png")));
    textures.push_back(
        LoadTextureFromImage(LoadImage("assets/Block/Pieces2.png")));
    textures.push_back(
        LoadTextureFromImage(LoadImage("assets/Block/Pieces3.png")));
    textures.push_back(
        LoadTextureFromImage(LoadImage("assets/Block/Pieces4.png")));
    entity->getComponent<TextureComponent>().addTexture("Normal", textures,
                                                        0.1f, true);
    entity->getComponent<PositionComponent>().setPosition(fixedPosition);
    entity->getComponent<TextureComponent>().changeState("Normal");
  } else if (sumFrame >= 0.2f) {
    entity->removeComponent<BoundingBoxComponent>();
    entity->removeComponent<TextureComponent>();
    retVal = nullptr;
  }
  return retVal;
}

// QuestionBlock
TriggerQuestionBlock::TriggerQuestionBlock() { sumFrame = 0.0f; }
TriggerQuestionBlock::TriggerQuestionBlock(Vector2 _fixedPosition) {
  sumFrame = 0.0f;
  fixedPosition = _fixedPosition;
}
TriggerBehaviour *TriggerQuestionBlock::trigger(AbstractEntity *entity,
                                                float deltaTime) {
  // entity->notify();
  TriggerBehaviour *retVal = this;
  sumFrame += deltaTime;
  Vector2 velocity = entity->getComponent<TransformComponent>().getVelocity();
  if (sumFrame < 0.1f) {
    velocity = velocity + (Vector2){0.0f, -600.0f * deltaTime};
  }
  velocity = velocity + (Vector2){0.0f, 240.0f * deltaTime};
  if (velocity.y >= 600.0f)
    velocity.y = 600.0f;
  if (velocity.y <= -600.0f)
    velocity.y = -600.0f;
  if (sumFrame >= 0.3f) {
    createHardBlock(fixedPosition);
    entity->destroy();
    retVal = nullptr;
    return retVal;
  }
  entity->getComponent<TransformComponent>().setVelocity(velocity);

  return retVal;
}
