#include "Components/CharacterState.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Texture.h"
#include "EventManager.h"
#include "System/System.h"

void PlayerSystem::onMarioJumpOnGoomba(const Event &event) {
  ASSERT(event.type == EventType::MarioJumpOnGoomba);
  const auto &MJOG = std::get<MarioJumpOnGoombaEvent>(event.data);
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MJOG.marioID);
  auto _goomba = EM.getEntityPtr(MJOG.goombaID);

  ASSERT(!_mario.expired());
  ASSERT(!_goomba.expired());

  auto mario = _mario.lock();
  auto goomba = _goomba.lock();

  goomba->getComponent<TextureComponent>().changeState("Die");
}

void PlayerSystem::configure() {
  EventQueue &EQ = EventQueue::getInstance();
  EQ.registerHandler(EventType::MarioJumpOnGoomba, this->onMarioJumpOnGoomba);
}

void PlayerSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<PlayerTag>();
  for (auto tEntity : Entities) {
    Vector2 velocity =
        tEntity.lock()->getComponent<TransformComponent>().getVelocity();
    Vector2 position =
        tEntity.lock()->getComponent<PositionComponent>().getPosition();
    auto &playerConstant =
        tEntity.lock()->getComponent<CharacterParametersComponent>();
    auto &state = tEntity.lock()->getComponent<CharacterStateComponent>();
    bool keyLeft = IsKeyDown(KEY_LEFT);
    bool keyRight = IsKeyDown(KEY_RIGHT);
    bool keyUp = IsKeyDown(KEY_UP);
    bool keyDown = IsKeyDown(KEY_DOWN);
    if (state.getState() != "JUMPING" && state.getState() != "DROPPING") {
      if (std::fabs(velocity.x) < playerConstant.MIN_WALKING_VELO) {
        velocity.x = 0.0f;
        if (keyLeft && !keyDown) {
          velocity.x -= playerConstant.MIN_WALKING_VELO;
        }
        if (keyRight && !keyDown) {
          velocity.x += playerConstant.MIN_WALKING_VELO;
        }
      } else if (std::fabs(velocity.x) >= playerConstant.MIN_WALKING_VELO) {
        if (state.getFacing() == "RIGHT") {
          if (keyRight && !keyLeft && !keyDown) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
              velocity.x += playerConstant.RUNNING_ACC * dt;
            } else
              velocity.x += playerConstant.WALKING_ACC * dt;
          } else if (keyLeft && !keyRight && !keyDown) {
            velocity.x -= playerConstant.SKIDDING_DEC * dt;
            state.setEnumState("SKIDDING");
          } else {
            velocity.x -= playerConstant.NORMAL_DEC * dt;
          }
        }
        if (state.getFacing() == "LEFT") {
          if (keyLeft && !keyRight && !keyDown) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
              velocity.x -= playerConstant.RUNNING_ACC * dt;
            } else
              velocity.x -= playerConstant.WALKING_ACC * dt;
          } else if (keyRight && !keyLeft && !keyDown) {
            velocity.x += playerConstant.SKIDDING_DEC * dt;
            state.setEnumState("SKIDDING");
          } else {
            velocity.x += playerConstant.NORMAL_DEC * dt;
          }
        }
      }
      velocity.y += playerConstant.fallAcc * dt;

      if (IsKeyPressed(KEY_UP)) {
        velocity.y = playerConstant.JUMPING_VELO;
        playerConstant.fallAcc = playerConstant.FALL_ACC;
        state.setEnumState("JUMPING");
        if (state.getSize() == "SMALL")
          tEntity.lock()
              ->getComponent<MarioSoundComponent>()
              .PlayJumpSmallEffect();
        else if (state.getSize() == "LARGE")
          tEntity.lock()
              ->getComponent<MarioSoundComponent>()
              .PlayJumpSuperEffect();
      }

      if (keyDown && std::fabs(velocity.x) < playerConstant.MIN_WALKING_VELO &&
          state.getSize() == "LARGE" && state.getState() != "DUCKLING") {
        state.setEnumState("DUCKLING");
        tEntity.lock()->getComponent<BoundingBoxComponent>().setSize(
            {16.0f, 16.0f});
        tEntity.lock()->getComponent<PositionComponent>().setPosition(
            {position.x, position.y + 13.0f});
      }
      if (IsKeyReleased(KEY_DOWN) && state.getState() == "DUCKLING") {
        state.setEnumState("IDLE");
        tEntity.lock()->getComponent<BoundingBoxComponent>().setSize(
            {16.0f, 28.0f});
        tEntity.lock()->getComponent<PositionComponent>().setPosition(
            {position.x, position.y - 13.0f});
      }
    } else {
      if (velocity.y < 0.0f && IsKeyDown(KEY_UP)) {
        velocity.y -=
            (playerConstant.FALL_ACC - playerConstant.FALL_ACC_A) * dt;
      }
      if (keyRight && !keyLeft) {
        if (fabs(velocity.x) > playerConstant.MAX_WALKING_VELO)
          velocity.x += playerConstant.RUNNING_ACC * dt;
        else
          velocity.x += playerConstant.WALKING_ACC * dt;
      } else if (keyLeft && !keyRight) {
        if (fabs(velocity.x) > playerConstant.MAX_WALKING_VELO)
          velocity.x -= playerConstant.RUNNING_ACC * dt;
        else
          velocity.x -= playerConstant.WALKING_ACC * dt;
      }
      if (velocity.y > 0.0f && state.getState() == "JUMPING")
        state.setEnumState("DROPPING");
      velocity.y += playerConstant.fallAcc * dt;
    }
    if (velocity.y >= playerConstant.MAX_FALL)
      velocity.y = playerConstant.MAX_FALL;
    if (velocity.y <= -playerConstant.MAX_FALL)
      velocity.y = -playerConstant.MAX_FALL;

    if (velocity.x >= playerConstant.MAX_RUNNING_VELO)
      velocity.x = playerConstant.MAX_RUNNING_VELO;
    if (velocity.x <= -playerConstant.MAX_RUNNING_VELO)
      velocity.x = -playerConstant.MAX_RUNNING_VELO;
    if (velocity.x >= playerConstant.MAX_WALKING_VELO &&
        !IsKeyDown(KEY_LEFT_SHIFT))
      velocity.x = playerConstant.MAX_WALKING_VELO;
    if (velocity.x <= -playerConstant.MAX_WALKING_VELO &&
        !IsKeyDown(KEY_LEFT_SHIFT))
      velocity.x = -playerConstant.MAX_WALKING_VELO;

    if (velocity.x < 0.0f)
      state.setFacingState("LEFT");
    if (velocity.x > 0.0f)
      state.setFacingState("RIGHT");
    if (state.getState() == "SKIDDING") {
      if (std::fabs(velocity.x) < playerConstant.MIN_SKIDDING)
        state.setEnumState("IDLE");
    } else if (state.getState() != "JUMPING" &&
               state.getState() != "DROPPING" &&
               state.getState() != "DUCKLING") {
      if (std::fabs(velocity.x) >= playerConstant.MIN_WALKING_VELO) {
        state.setEnumState("MOVING");
      } else {
        state.setEnumState("IDLE");
      }
    }
    tEntity.lock()->getComponent<TextureComponent>().changeState(
        state.getCurrentState());
    tEntity.lock()->getComponent<TransformComponent>().setVelocity(velocity);

    auto below = tEntity.lock()->getComponent<CollisionComponent>().getBelow();
    if (!below.expired()) {
      auto belowEntity = below.lock();
      if (belowEntity->hasComponent<EnemyTag>()) {
        EventQueue &EQ = EventQueue::getInstance();
        Event event(EventType::MarioJumpOnGoomba,
                    MarioJumpOnGoombaEvent{tEntity.lock()->getID(),
                                           belowEntity->getID()});
        EQ.pushEvent(event);
      }
    }
  }
}
