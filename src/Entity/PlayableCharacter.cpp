#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Components/SoundComponent.h"
#include "Entity/PlayableEntity.h"
#include "Entity/States/CharacterStates.h"

PlayableEntity::PlayableEntity(std::string name) : AbstractEntity(name) {}

void PlayableEntity::setVelocity(Vector2 newVelocity) {
  ASSERT(hasComponent<TransformComponent>());
  getComponent<TransformComponent>().setVelocity(newVelocity);
}

Vector2 PlayableEntity::getVelocity() {
  ASSERT(hasComponent<TransformComponent>());
  return getComponent<TransformComponent>().getVelocity();
}

Luigi::Luigi()
    : PlayableEntity("Luigi"),
      state(new DroppingState({0.0f, 1.0f}, "LARGE", "RIGHT", "DROPPING")) {
  Vector2 size({16, 20});
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0, 0};

  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity);
  addComponent<BoundingBoxComponent>(size);
  addComponent<RigidBodyComponent>();
  addComponent<TextureComponent>();
  addComponent<MarioSoundComponent>();
  addComponent<CollisionComponent>();

  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-IDLE", "./assets/Luigi/Small-Right-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-MOVING", "./assets/Luigi/Small-Right-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-SKIDDING", "./assets/Luigi/Small-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-JUMPING", "./assets/Luigi/Small-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-DROPPING", "./assets/Luigi/Small-Right-Dropping.png");

  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-IDLE", "./assets/Luigi/Small-Left-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-MOVING", "./assets/Luigi/Small-Left-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-SKIDDING", "./assets/Luigi/Small-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-JUMPING", "./assets/Luigi/Small-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-DROPPING", "./assets/Luigi/Small-Left-Dropping.png");

  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-IDLE", "./assets/Luigi/Large-Right-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-MOVING", "./assets/Luigi/Large-Right-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-SKIDDING", "./assets/Luigi/Large-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-JUMPING", "./assets/Luigi/Large-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-DROPPING", "./assets/Luigi/Large-Right-Dropping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-DUCKLING", "./assets/Luigi/Large-Right-Duckling.png");

  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-IDLE", "./assets/Luigi/Large-Left-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-MOVING", "./assets/Luigi/Large-Left-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-SKIDDING", "./assets/Luigi/Large-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-JUMPING", "./assets/Luigi/Large-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-DROPPING", "./assets/Luigi/Large-Left-Dropping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-DUCKLING", "./assets/Luigi/Large-Left-Duckling.png");

  getComponent<MarioSoundComponent>().LoadSounds();
}
void Luigi::update() {
  input();
  state->update(*this);
  for (auto &component : components) {
    component->update();
  }

  // check collision
  // for ( .. )
  // getComponent<BoundingBoxComponent>().checkCollision()
}
void Luigi::input() {
  if (CharacterState *newState = state->handleInput(*this)) {
    state = Unique<CharacterState>(newState);
  }
}

void Luigi::draw() {
  ASSERT(hasComponent<TextureComponent>());
  std::string currentState = state->getCurrentState();
  getComponent<TextureComponent>().drawTexture(currentState);
}
Mario::Mario()
    : PlayableEntity("Mario"),
      state(new DroppingState({0.0f, 1.0f}, "SMALL", "RIGHT", "DROPPING")) {
  Vector2 size({16, 20});
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0, 0};

  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity);
  addComponent<BoundingBoxComponent>(size);
  addComponent<RigidBodyComponent>();
  addComponent<TextureComponent>();
  addComponent<MarioSoundComponent>();
  addComponent<CollisionComponent>();

  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-IDLE", "./assets/Mario/Small-Right-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-MOVING", "./assets/Mario/Small-Right-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-SKIDDING", "./assets/Mario/Small-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-JUMPING", "./assets/Mario/Small-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-RIGHT-DROPPING", "./assets/Mario/Small-Right-Dropping.png");

  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-IDLE", "./assets/Mario/Small-Left-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-MOVING", "./assets/Mario/Small-Left-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-SKIDDING", "./assets/Mario/Small-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-JUMPING", "./assets/Mario/Small-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "SMALL-LEFT-DROPPING", "./assets/Mario/Small-Left-Dropping.png");

  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-IDLE", "./assets/Mario/Large-Right-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-MOVING", "./assets/Mario/Large-Right-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-SKIDDING", "./assets/Mario/Large-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-JUMPING", "./assets/Mario/Large-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-DROPPING", "./assets/Mario/Large-Right-Dropping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-RIGHT-DUCKLING", "./assets/Mario/Large-Right-Duckling.png");

  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-IDLE", "./assets/Mario/Large-Left-Idle.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-MOVING", "./assets/Mario/Large-Left-Moving.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-SKIDDING", "./assets/Mario/Large-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-JUMPING", "./assets/Mario/Large-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-DROPPING", "./assets/Mario/Large-Left-Dropping.png");
  getComponent<TextureComponent>().addTexture(
      "LARGE-LEFT-DUCKLING", "./assets/Mario/Large-Left-Duckling.png");

  getComponent<MarioSoundComponent>().LoadSounds();
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
  std::string currentState = state->getCurrentState();
  getComponent<TextureComponent>().drawTexture(currentState);
}
