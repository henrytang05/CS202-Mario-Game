#include "Entity/PlayableEntity.h"
#include "AbstractEntity.h"
#include "Components/BoundingBox.h"
#include "Components/Components_include.h"
#include "Components/SoundComponent.h"
#include "Components/Tags.h"
#include "Entity/States/CharacterStates.h"

PlayableEntity::PlayableEntity(std::string name)
    : AbstractEntity(name), fallAcc(GRAVITY_DEC), isDeath(false), gameOver(false),
      state(make_shared<DroppingState>("SMALL", "RIGHT")) {

  addComponent<PlayerTag>();
}
PlayableEntity::~PlayableEntity() {
  state = nullptr;
}
PlayableEntity::PlayableEntity() : fallAcc(GRAVITY_DEC), state(make_shared<DroppingState>("SMALL", "RIGHT")), isDeath(false), gameOver(false) {
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

bool PlayableEntity::checkOver() const {
  return gameOver;
}
void PlayableEntity::setToDie() {
  state = make_shared<DeathState>("SMALL", state->getFacing());
  getComponent<MarioSoundComponent>().PlayMarioDieEffect();
}
void PlayableEntity::setToSmall() {
  state->setSizeState("SMALL");
  getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 20.0f});
  Vector2 position = getComponent<PositionComponent>().getPosition();
  getComponent<PositionComponent>().setPosition((Vector2){position.x, position.y + 8.0f});
}
void PlayableEntity::setToLarge() {
  state->setSizeState("LARGE");
  getComponent<BoundingBoxComponent>().setSize((Vector2){16.0f, 28.0f});
  Vector2 position = getComponent<PositionComponent>().getPosition();
  getComponent<PositionComponent>().setPosition((Vector2){position.x, position.y - 8.0f});
}
void PlayableEntity::collisionRight() {
  auto right = getComponent<CollisionComponent>().getRight();
  if(right.lock() != nullptr) {
    if(right.lock()->hasComponent<EnemyTag>()) {
      if(state->getSize() == "SMALL")
        setToDie();
      else {
        setToSmall();
      }
    }
  }
}
void PlayableEntity::collisionLeft() {
  auto left = getComponent<CollisionComponent>().getLeft();
  if(left.lock() != nullptr) {
    if(left.lock()->hasComponent<EnemyTag>()) {
      if(state->getSize() == "SMALL")
        setToDie();
      else {
        setToSmall();
      }
    }
  } 
}
void PlayableEntity::collisionAbove() {
  auto above = getComponent<CollisionComponent>().getAbove();
  if(above.lock()) {
    if(above.lock()->name == "BrokenBlock") {
      if(state->getSize() == "SMALL") {
        above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new TriggerBrokenBlockWhenHitBySmall(above.lock()->getComponent<PositionComponent>().getPosition()));
        getComponent<MarioSoundComponent>().PlayBumpEffect();
      }
      else{
        above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new TriggerBrokenBlockWhenHitByLarge(above.lock()->getComponent<PositionComponent>().getPosition()));
        getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
      }
    }
    if(above.lock()->name == "QuestionBlock")
    {
      above.lock()->getComponent<BlockTriggerComponent>().setTrigger(new TriggerQuestionBlock(above.lock()->getComponent<PositionComponent>().getPosition()));
      getComponent<MarioSoundComponent>().PlayBumpEffect();
    }
    if(above.lock()->hasComponent<EnemyTag>()) {
      if(state->getSize() == "SMALL")
        setToDie();
      else {
        setToSmall();
      }
    }
  }
}
void PlayableEntity::collisionBelow() {
  auto below = getComponent<CollisionComponent>().getBelow();
  if(below.lock() != nullptr) {
    if(below.lock()->hasComponent<EnemyTag>()) {
      if(below.lock()->name == "Piranha") {
        if(state->getSize() == "SMALL")
          setToDie();
        else {
          setToSmall();
        }
      }
      if(below.lock()->hasComponent<CollisionComponent>())
        below.lock()->getComponent<CollisionComponent>().setAbove(Shared<PlayableEntity>(this));
    }
  }
}
void PlayableEntity::resolveCollision() {
  collisionAbove();
  collisionBelow();
  collisionLeft();
  collisionRight();
}
void PlayableEntity::update(float deltaTime) {
  if(getComponent<PositionComponent>().getY() > 1.2f * screenHeight) {
    setToDie();
  }
  if(state->getState() == "DEATH") {
    isDeath = true;
    getComponent<TextureComponent>().changeState(state->getCurrentState());
    getComponent<TransformComponent>().setVelocity({0.0f, -200.0f});
    getComponent<TransformComponent>().update(deltaTime);
    if(getComponent<PositionComponent>().getPosition().y < 0.0f) {
      gameOver = true;
    }
    return;
  }
  handleInput(deltaTime);
  getComponent<CollisionComponent>().reset();
  for (auto &component : components) {
    component->update(deltaTime);
  }

  // resolve collision
  resolveCollision();
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
    if (getComponent<CollisionComponent>().getBelow().lock() == nullptr)
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
    if (getComponent<CollisionComponent>().getBelow().lock() &&
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
  getComponent<TextureComponent>().changeState(state->getCurrentState());
  setVelocity(velocity);
}
