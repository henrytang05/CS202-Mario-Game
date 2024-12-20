#include "Entity/PlayableEntity.h"
#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Components/SoundComponent.h"
#include "Components/Tags.h"
#include "Entity/States/CharacterStates.h"

PlayableEntity::PlayableEntity(std::string name)
    : AbstractEntity(name), fallAcc(GRAVITY_DEC), isDeath(false),
      state(make_shared<DroppingState>("SMALL", "RIGHT")) {

  addComponent<PlayerTag>();
}

PlayableEntity::PlayableEntity() : fallAcc(GRAVITY_DEC), state(make_shared<DroppingState>("SMALL", "RIGHT")), isDeath(false) {
  addComponent<PlayerTag>();
}
void PlayableEntity::setVelocity(Vector2 newVelocity) {
  ASSERT(hasComponent<TransformComponent>());
  getComponent<TransformComponent>().setVelocity(newVelocity);
}

Vector2 PlayableEntity::getVelocity() {
  ASSERT(hasComponent<TransformComponent>());
  return getComponent<TransformComponent>().getVelocity();
}
bool PlayableEntity::checkAlive() const {
  return !isDeath;
}
void PlayableEntity::update(float deltaTime) {
  if(getComponent<PositionComponent>().getY() > 1.2f * screenHeight) {
    state = make_shared<DeathState>("SMALL", state->getFacing());
    getComponent<MarioSoundComponent>().PlayMarioDieEffect();
  }
  if(state->getState() == "DEATH") {
    getComponent<TextureComponent2>().changeState(state->getCurrentState());
    getComponent<TransformComponent>().setVelocity({0.0f, -200.0f});
    getComponent<TransformComponent>().update(deltaTime);
    if(getComponent<PositionComponent>().getPosition().y < 0.0f) {
      isDeath = true;
    }
    return;
  }
  handleInput(deltaTime);
  getComponent<CollisionComponent>().reset();
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
        getComponent<MarioSoundComponent>().PlayBumpEffect();
    }
  }
  if(below != nullptr) {
    if(below->hasComponent<EnemyTag>()) {
      if(below->hasComponent<CollisionComponent>())
        below->getComponent<CollisionComponent>().setAbove(make_shared<PlayableEntity>("Player"));
    }
  }
  if(left != nullptr) {
    if(left->hasComponent<EnemyTag>() && state->getSize() == "SMALL") {
      state = make_shared<DeathState>(state->getSize(), state->getFacing());
      getComponent<MarioSoundComponent>().PlayMarioDieEffect();
    }
  }   
  if(right != nullptr) {
    if(right->hasComponent<EnemyTag>() && state->getSize() == "SMALL") {
      state = make_shared<DeathState>(state->getSize(), state->getFacing());
      getComponent<MarioSoundComponent>().PlayMarioDieEffect();
    }
  } 
}
void PlayableEntity::draw() {
}
void PlayableEntity::handleInput(float deltaTime) {
  
  Vector2 velocity = getVelocity();
  bool keyLeft = IsKeyDown(KEY_LEFT);
  bool keyRight = IsKeyDown(KEY_RIGHT);
  bool keyUp = IsKeyDown(KEY_UP);
  bool keyDown = IsKeyDown(KEY_DOWN);
  if (state->getState() != "JUMPING" && state->getState() != "DROPPING") {
    if (getComponent<CollisionComponent>().getBelow() == nullptr)
      state = make_shared<DroppingState>(state->getSize(), state->getFacing());
    if (std::fabs(velocity.x) < MIN_WALKING_VELO) {
      velocity.x = 0.0f;
      if (keyLeft && !keyDown) {
        velocity.x -= MIN_WALKING_VELO;
      }
      if (keyRight && !keyDown) {
        velocity.x += MIN_WALKING_VELO;
      }
    } else if (std::fabs(velocity.x) >= MIN_WALKING_VELO) {
      if (state->getFacing() == "RIGHT") {
        if (keyRight && !keyLeft && !keyDown) {
          if (IsKeyDown(KEY_LEFT_SHIFT)) {
            velocity.x += RUNNING_ACC * deltaTime;
          } else
            velocity.x += WALKING_ACC * deltaTime;
        } else if (keyLeft && !keyRight && !keyDown) {
          velocity.x -= SKIDDING_DEC * deltaTime;
          state =
              make_shared<SkiddingState>(state->getSize(), state->getFacing());
        } else {
          velocity.x -= NORMAL_DEC * deltaTime;
        }
      }
      if (state->getFacing() == "LEFT") {
        if (keyLeft && !keyRight && !keyDown) {
          if (IsKeyDown(KEY_LEFT_SHIFT)) {
            velocity.x -= RUNNING_ACC * deltaTime;
          } else
            velocity.x -= WALKING_ACC * deltaTime;
        } else if (keyRight && !keyLeft && !keyDown) {
          velocity.x += SKIDDING_DEC * deltaTime;
          state =
              make_shared<SkiddingState>(state->getSize(), state->getFacing());
        } else {
          velocity.x += NORMAL_DEC * deltaTime;
        }
      }
    }
    velocity.y += fallAcc * deltaTime;

    if (IsKeyPressed(KEY_UP)) {
      velocity.y = JUMPING_VELO;
      fallAcc = FALL_ACC;
      state = make_shared<JumpingState>(state->getSize(), state->getFacing());
      if (state->getSize() == "SMALL")
        getComponent<MarioSoundComponent>().PlayJumpSmallEffect();
      else if (state->getSize() == "LARGE")
        getComponent<MarioSoundComponent>().PlayJumpSuperEffect();
    }

    if (keyDown && std::fabs(velocity.x) < MIN_WALKING_VELO &&
        state->getSize() == "LARGE" && state->getState() != "DUCKLING") {
      state = make_shared<DucklingState>(state->getSize(), state->getFacing());
      getComponent<BoundingBoxComponent>().setSize({16.0f, 15.0f});
      getComponent<PositionComponent>().setPosition(
          {getComponent<PositionComponent>().getX(),
           getComponent<PositionComponent>().getY() + 13.0f});
    }
    if (IsKeyReleased(KEY_DOWN) && state->getState() == "DUCKLING") {
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
      getComponent<BoundingBoxComponent>().setSize({16.0f, 28.0f});
      getComponent<PositionComponent>().setPosition(
          {getComponent<PositionComponent>().getX(),
           getComponent<PositionComponent>().getY() - 13.0f});
    }
  } else {
    if (velocity.y < 0.0f && IsKeyDown(KEY_UP)) {
      velocity.y -= (FALL_ACC - FALL_ACC_A) * deltaTime;
    }
    if (keyRight && !keyLeft) {
      if (fabs(velocity.x) > MAX_WALKING_VELO)
        velocity.x += RUNNING_ACC * deltaTime;
      else
        velocity.x += WALKING_ACC * deltaTime;
    } else if (keyLeft && !keyRight) {
      if (fabs(velocity.x) > MAX_WALKING_VELO)
        velocity.x -= RUNNING_ACC * deltaTime;
      else
        velocity.x -= WALKING_ACC * deltaTime;
    }
    if (velocity.y > 0.0f && state->getState() != "DROPPING")
      state = make_shared<DroppingState>(state->getSize(), state->getFacing());
    if (getComponent<CollisionComponent>().getBelow() &&
        state->getState() == "DROPPING") {
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
      // fallAcc = GRAVITY_DEC;
    }
    velocity.y += fallAcc * deltaTime;
  }
  if (velocity.y >= MAX_FALL)
    velocity.y = MAX_FALL;
  if (velocity.y <= -MAX_FALL)
    velocity.y = -MAX_FALL;

  if (velocity.x >= MAX_RUNNING_VELO)
    velocity.x = MAX_RUNNING_VELO;
  if (velocity.x <= -MAX_RUNNING_VELO)
    velocity.x = -MAX_RUNNING_VELO;
  if (velocity.x >= MAX_WALKING_VELO && !IsKeyDown(KEY_LEFT_SHIFT))
    velocity.x = MAX_WALKING_VELO;
  if (velocity.x <= -MAX_WALKING_VELO && !IsKeyDown(KEY_LEFT_SHIFT))
    velocity.x = -MAX_WALKING_VELO;

  if (velocity.x < 0.0f)
    state->setFacingState("LEFT");
  if (velocity.x > 0.0f)
    state->setFacingState("RIGHT");
  if (state->getState() == "SKIDDING") {
    if (std::fabs(velocity.x) < MIN_SKIDDING)
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
  } else if (state->getState() != "JUMPING" &&
             state->getState() != "DROPPING" &&
             state->getState() != "DUCKLING") {
    if (std::fabs(velocity.x) >= MIN_WALKING_VELO) {
          state = make_shared<MovingState>(state->getSize(), state->getFacing());
    } else {
      state = make_shared<StandingState>(state->getSize(), state->getFacing());
    }
  }
  getComponent<TextureComponent2>().changeState(state->getCurrentState());
  setVelocity(velocity);
}
