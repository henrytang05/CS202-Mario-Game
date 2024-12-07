#include "Entity/Entity.h"
#include "Entity/PlayableEntity.h"

#include "Components/Components_include.h"

PlayableEntity::PlayableEntity(std::string name) : Entity(name) {}

void PlayableEntity::setVelocity(Vector2 newVelocity) {
  ASSERT(hasComponent<TransformComponent>());
  getComponent<TransformComponent>().setVelocity(newVelocity);
}

Vector2 PlayableEntity::getVelocity() {
  ASSERT(hasComponent<TransformComponent>());
  return getComponent<TransformComponent>().getVelocity();
}

bool PlayableEntity::isOnTheGround() {
  ASSERT(hasComponent<BoundingBoxComponent>());
  return getComponent<BoundingBoxComponent>().isOnTheGround();
}

Mario::Mario()
    : PlayableEntity("Mario"), state(new NewStandingState({0.5f, 0.0f})) {
  Vector2 size({16, 23});
  Vector2 position = {0, (float)ground - size.y};
  Vector2 velocity = {0, 0};

  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity, .1);
  addComponent<BoundingBoxComponent>(size);
  addComponent<RigidBodyComponent>();
  addComponent<TextureComponent>("./assets/Mario-Small", 11);
}

void Mario::update() { state->update(*this); }

void Mario::input() {
  Unique<NewCharacterState> newState(state->handleInput(*this));
}
