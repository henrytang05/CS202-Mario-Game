#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include "Entity/Entity.h"
class NewCharacterState {
public:
  NewCharacterState() = default;
  virtual ~NewCharacterState() = default;
  virtual NewCharacterState *handleInput(Entity &character) = 0;
  virtual void update(Entity &character) = 0;
};

class NewStandingState : public NewCharacterState {
public:
  NewStandingState() = default;
  NewStandingState(Vector2 _fraction);
  ~NewStandingState() = default;
  NewCharacterState *handleInput(Entity &character) override;
  void update(Entity &character) override;

private:
  Vector2 fraction;
};

class NewJumpingState : public NewCharacterState {
public:
  NewJumpingState() = default;
  ~NewJumpingState() = default;
  NewJumpingState(Vector2 _fraction);
  NewCharacterState *handleInput(Entity &character) override;
  void update(Entity &character) override;

private:
  Vector2 fraction;
};

class NewMovingState : public NewCharacterState {
public:
  NewMovingState() = default;
  ~NewMovingState() = default;
  NewMovingState(Vector2 _velocity);
  NewCharacterState *handleInput(Entity &character) override;
  void update(Entity &character) override;

private:
  Vector2 velocity;
  int frameDelay, frameDelayCounter, frameIndex;
};

class NewDroppingState : public NewCharacterState {
public:
  NewDroppingState() = default;
  ~NewDroppingState() = default;
  NewDroppingState(Vector2 _fraction);
  NewCharacterState *handleInput(Entity &character) override;
  void update(Entity &character) override;

private:
  Vector2 fraction;
  int frameDelay, frameDelayCounter, frameIndex;
};

#endif // CHARACTER_STATE_H
