#include "AbstractEntity.h"
#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"

PlayableEntity::PlayableEntity(std::string name) : AbstractEntity(name) {}

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
    : PlayableEntity("Mario"), state(new StandingState({0.5f, 0.0f})) {
  Vector2 size({16, 23});
  Vector2 position = {0, (float)ground - size.y};
  Vector2 velocity = {0, 0};

  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity, .1);
  addComponent<BoundingBoxComponent>(size);
  addComponent<RigidBodyComponent>();
  addComponent<TextureComponent>("./assets/Mario-Small", 11);
}

void Mario::update() {
  input();
  state->update(*this);
  for (auto &component : components) {
    component->update();
  }
}

void Mario::input() {
  if (CharacterState *newState = state->handleInput(*this)) {
    state = Unique<CharacterState>(newState);
  }
}

void Mario::draw() {
  ASSERT(hasComponent<TextureComponent>());
  getComponent<TextureComponent>().drawTexture();
}
