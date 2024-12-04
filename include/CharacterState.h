#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H
#include "pch.h"
#include "globals.h"
class Character;
class CharacterState {
public:
  virtual ~CharacterState() = default;
  virtual CharacterState* handleInput(Character &character) = 0;
  virtual void update(Character &character) = 0;
};
class JumpingState : public CharacterState {
public:
  Vector2 fraction;
  JumpingState() = default;
  ~JumpingState() = default;
  JumpingState(Vector2 _fraction);
  CharacterState* handleInput(Character &character) override;
  void update(Character &character) override;
};
class DroppingState : public CharacterState {
public:
  Vector2 fraction;
  DroppingState() = default;
  ~DroppingState() = default;
  DroppingState(Vector2 _fraction);
  CharacterState* handleInput(Character &character) override;
  void update(Character &character) override;
};
class StandingState : public CharacterState {
public:
  Vector2 fraction;
  StandingState() = default;
  ~StandingState() = default;
  StandingState(Vector2 _fraction);
  CharacterState* handleInput(Character &character) override;
  void update(Character &character) override;
};
class MovingState : public CharacterState {
public:
  Vector2 velocity;
  int frameDelay, frameDelayCounter, frameIndex;
  MovingState() = default;
  ~MovingState() = default;
  MovingState(Vector2 _velocity);
  CharacterState* handleInput(Character &character) override;
  void update(Character &character) override;
};

#endif // CHARACTERSTATE_H