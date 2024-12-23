#include "Components/BlockTrigger.h"

//BlockTriggerComponent
BlockTriggerComponent::BlockTriggerComponent() : Component("BlockTriggerComponent"), trigger(nullptr) {}
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
