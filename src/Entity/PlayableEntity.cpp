#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Entity/PlayableEntity.h"
#include "Entity/States/CharacterStates.h"
#include "Components/SoundComponent.h"

PlayableEntity::PlayableEntity(std::string name) : AbstractEntity(name), fallAcc(GRAVITY_DEC), timeFrameCounter(0.0f), state(make_shared<DroppingState>("SMALL", "RIGHT")) {}

void PlayableEntity::setVelocity(Vector2 newVelocity) {
  ASSERT(hasComponent<TransformComponent>());
  getComponent<TransformComponent>().setVelocity(newVelocity);
}

Vector2 PlayableEntity::getVelocity() {
  ASSERT(hasComponent<TransformComponent>());
  return getComponent<TransformComponent>().getVelocity();
}
void PlayableEntity::update(float deltaTime) {
  handleInput(state, deltaTime);
  for (auto &component : components) {
    component->update(deltaTime);
  }

  // resolve collision
  Shared<AbstractEntity> above = getComponent<CollisionComponent>().getAbove();
  Shared<AbstractEntity> below = getComponent<CollisionComponent>().getBelow();
  Shared<AbstractEntity> left = getComponent<CollisionComponent>().getLeft();
  Shared<AbstractEntity> right = getComponent<CollisionComponent>().getRight();
  if(above) {
    if(above->name == "BrokenBlock") {
      if(state->getSize() == "SMALL")
        above->getComponent<BlockTriggerComponent>().setTrigger(new TriggerBrokenBlockWhenHitBySmall(above->getComponent<PositionComponent>().getPosition()));
    }
  }
  // if(getComponent<CollisionComponent>().getBelow())
  //   cerr << getComponent<CollisionComponent>().getBelow()->name << '\n';
  // if(getComponent<CollisionComponent>().getLeft())
  //   cerr << getComponent<CollisionComponent>().getLeft()->name << '\n';
  // if(getComponent<CollisionComponent>().getRight())
  //   cerr << getComponent<CollisionComponent>().getRight()->name << '\n';
}
void PlayableEntity::draw() {
  ASSERT(hasComponent<TextureComponent>());
  std::string currentState = state->getCurrentState();
  getComponent<TextureComponent>().drawTexture(currentState);
}
PlayableEntity::PlayableEntity() {
  timeFrameCounter = 0.0f;
  fallAcc = GRAVITY_DEC;
}
void PlayableEntity::handleInput(Shared<CharacterState> &state, float deltaTime) {
  Vector2 velocity = getVelocity();
  bool keyLeft = IsKeyDown(KEY_LEFT);
  bool keyRight = IsKeyDown(KEY_RIGHT);
  bool keyUp = IsKeyDown(KEY_UP);
  bool keyDown = IsKeyDown(KEY_DOWN);
  if(state->getState() != "JUMPING" && state->getState() != "DROPPING") {
    if(getComponent<CollisionComponent>().getBelow() == nullptr) state = make_shared<DroppingState>(state->getSize(), state->getFacing());
    if(std::fabs(velocity.x) < MIN_WALKING_VELO) {
      velocity.x = 0.0f;
      if(keyLeft && !keyDown) {
        velocity.x -= MIN_WALKING_VELO;
      }
      if(keyRight && !keyDown) {
        velocity.x += MIN_WALKING_VELO;
      }
    }
    else if(std::fabs(velocity.x) >= MIN_WALKING_VELO) {
      if(state->getFacing() == "RIGHT") {
        if(keyRight && !keyLeft && !keyDown) {
          if(IsKeyDown(KEY_LEFT_SHIFT)) {
            velocity.x += RUNNING_ACC * deltaTime;
          }
          else velocity.x += WALKING_ACC * deltaTime;
        }
        else if(keyLeft && !keyRight && !keyDown) {
          velocity.x -= SKIDDING_DEC * deltaTime;
          state = make_shared<SkiddingState>(state->getSize(), state->getFacing());
        }
        else {
          velocity.x -= NORMAL_DEC * deltaTime;
        }
      }
      if(state->getFacing() == "LEFT") {
        if(keyLeft && !keyRight && !keyDown) {
          if(IsKeyDown(KEY_LEFT_SHIFT)) {
            velocity.x -= RUNNING_ACC * deltaTime;
          }
          else velocity.x -= WALKING_ACC * deltaTime;
        }
        else if(keyRight && !keyLeft && !keyDown) {
          velocity.x += SKIDDING_DEC * deltaTime;
          state = make_shared<SkiddingState>(state->getSize(), state->getFacing());
        }
        else {
          velocity.x += NORMAL_DEC * deltaTime;
        }
      }
    }
    velocity.y += fallAcc * deltaTime;

    if(IsKeyPressed(KEY_UP)) {
      velocity.y = JUMPING_VELO;
      fallAcc = FALL_ACC;
      state = make_shared<JumpingState>(state->getSize(), state->getFacing());
      if(state->getSize() == "SMALL")
        getComponent<MarioSoundComponent>().PlayJumpSmallEffect();
      else if(state->getSize() == "LARGE")
        getComponent<MarioSoundComponent>().PlayJumpSuperEffect();
    }

    if(keyDown && std::fabs(velocity.x) < MIN_WALKING_VELO && state->getSize() == "LARGE" && state->getState() != "DUCKLING") {
      state = make_shared<DucklingState>(state->getSize(), state->getFacing());
      getComponent<BoundingBoxComponent>().setSize({16.0f, 15.0f});
      getComponent<PositionComponent>().setPosition({getComponent<PositionComponent>().getX(), getComponent<PositionComponent>().getY() + 13.0f});
    }
    if(IsKeyReleased(KEY_DOWN) && state->getState() == "DUCKLING") {
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
      getComponent<BoundingBoxComponent>().setSize({16.0f, 28.0f});
      getComponent<PositionComponent>().setPosition({getComponent<PositionComponent>().getX(), getComponent<PositionComponent>().getY() - 13.0f});
    }
  }
  else {
    if(velocity.y < 0.0f && IsKeyDown(KEY_UP)) {
      velocity.y -= (FALL_ACC - FALL_ACC_A) * deltaTime;
    } 
    if(keyRight && !keyLeft) {
      if(fabs(velocity.x) > MAX_WALKING_VELO) velocity.x += RUNNING_ACC * deltaTime;
      else velocity.x += WALKING_ACC * deltaTime;
    }
    else if(keyLeft && !keyRight) {
      if(fabs(velocity.x) > MAX_WALKING_VELO) velocity.x -= RUNNING_ACC * deltaTime;
      else velocity.x -= WALKING_ACC * deltaTime;
    }
    if(velocity.y > 0.0f && state->getState() != "DROPPING") state = make_shared<DroppingState>(state->getSize(), state->getFacing());
    if(getComponent<CollisionComponent>().getBelow() && state->getState() == "DROPPING") { 
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
      //fallAcc = GRAVITY_DEC;
    }
    velocity.y += fallAcc * deltaTime;
  }
  if (velocity.y >= MAX_FALL) velocity.y = MAX_FALL;
  if (velocity.y <= -MAX_FALL) velocity.y = -MAX_FALL;

  if (velocity.x >= MAX_RUNNING_VELO) velocity.x = MAX_RUNNING_VELO;
  if (velocity.x <= -MAX_RUNNING_VELO) velocity.x = -MAX_RUNNING_VELO;
  if (velocity.x >= MAX_WALKING_VELO && !IsKeyDown(KEY_LEFT_SHIFT)) velocity.x = MAX_WALKING_VELO;
  if (velocity.x <= -MAX_WALKING_VELO && !IsKeyDown(KEY_LEFT_SHIFT)) velocity.x = -MAX_WALKING_VELO;

  if(velocity.x < 0.0f) state->setFacingState("LEFT");
  if(velocity.x > 0.0f) state->setFacingState("RIGHT");
  if(state->getState() == "SKIDDING") {
    if(std::fabs(velocity.x) < MIN_SKIDDING)
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
  } 
  else if(state->getState() != "JUMPING" && state->getState() != "DROPPING" && state->getState() != "DUCKLING") {
    if(std::fabs(velocity.x) >= MIN_WALKING_VELO) {
      timeFrameCounter += deltaTime;
      if(timeFrameCounter >= 0.1f) {
        if(state->getState() == "IDLE")
          state = make_shared<MovingState>(state->getSize(), state->getFacing());
        else 
          state = make_shared<StandingState>(state->getSize(), state->getFacing());
        timeFrameCounter = 0.0f;
      }
    }
    else {
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
      timeFrameCounter = 0.0f;
    }
  }
  setVelocity(velocity);
}
