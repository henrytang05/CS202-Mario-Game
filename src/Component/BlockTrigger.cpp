#include "Components/BlockTrigger.h"
#include "Components/Position.h"
TriggerBrokenBlockWhenHitBySmall::TriggerBrokenBlockWhenHitBySmall() {
  sumFrame = 0.0f;
}

TriggerBrokenBlockWhenHitBySmall::TriggerBrokenBlockWhenHitBySmall(
    Vector2 _fixedPosition) {
  fixedPosition = _fixedPosition;
  sumFrame = 0.0f;
}
// TriggerBrokenBlockWhenHitByLarge::TriggerBrokenBlockWhenHitByLarge() {
//     sumFrame = 0.0f;
// }

// TriggerQuestionBlock::TriggerQuestionBlock() {
//     sumFrame = 0.0f;
// }
// TriggerQuestionBlock::TriggerQuestionBlock(Vector2 _fixedPosition) {
//     sumFrame = 0.0f;
//     fixedPosition = _fixedPosition;
// }
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

// TriggerBehaviour* TriggerBrokenBlockWhenHitByLarge::trigger(AbstractEntity
// *entity, float deltaTime) {
//     TriggerBehaviour* retVal = this;
//     return retVal;
// }

// TriggerBehaviour* TriggerQuestionBlock::trigger(AbstractEntity *entity, float
// deltaTime) {
//     TriggerBehaviour *retVal = this;
//     sumFrame += deltaTime;
//     Vector2 velocity =
//     entity->getComponent<TransformComponent>().getVelocity(); if(sumFrame <
//     0.1f) {
//         velocity = velocity + (Vector2){0.0f, -600.0f * deltaTime};
//     }
//     velocity = velocity + (Vector2){0.0f, 240.0f * deltaTime};
//     if(velocity.y >= 600.0f) velocity.y = 600.0f;
//     if(velocity.y <= -600.0f) velocity.y = -600.0f;
//     if(sumFrame >= 0.3f) {
//         velocity.y = 0.0f;
//         retVal = nullptr;
//     }
//     entity->getComponent<TransformComponent>().setVelocity(velocity);
//     return retVal;
// }
BlockTriggerComponent::BlockTriggerComponent()
    : Component("BlockTriggerComponent"), trigger(nullptr) {}
BlockTriggerComponent::~BlockTriggerComponent() {
  if (trigger) {
    delete trigger;
    trigger = nullptr;
  }
}
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
    if (trigger->trigger(entity, deltaTime) == nullptr) {
      delete trigger;
      trigger = nullptr;
    }
  }
}
