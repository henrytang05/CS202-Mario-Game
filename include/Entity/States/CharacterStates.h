#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

class PlayableEntity;
const float WALKING_ACC = 0.1f;
const float RUNNING_ACC = 0.1f;
const float SKIDDING_DEC = 0.1f;
const float NORMAL_DEC = 0.3f;
const float JUMPPING_DEC = 5.0f;
const float JUMPING_ACC = 0.15f;
const float JUMPING_MOVING_ACC = 0.15f;
const float GRAVITY_DEC = 0.3f;
const float MAX_WALKING_VELO = 3.0f;
const float MAX_RUNNING_VELO = 4.0f;
const float MAX_JUMPING_VELO = 3.0f;
class CharacterState {
public:
  CharacterState() = default;
  virtual ~CharacterState() = default;
  virtual CharacterState *handleInput(PlayableEntity &character) = 0;
  virtual void update(PlayableEntity &character) = 0;
};

class StandingState : public CharacterState {
public:
  StandingState() = default;
  StandingState(Vector2 _friction);
  ~StandingState() = default;
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 friction;
};

class JumpingState : public CharacterState {
public:
  JumpingState() = default;
  ~JumpingState() = default;
  JumpingState(Vector2 _friction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 friction;
};

class MovingState : public CharacterState {
public:
  MovingState() = default;
  ~MovingState() = default;
  MovingState(Vector2 _velocity);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 velocity;
  int frameDelay, frameDelayCounter, frameIndex;
};
class DroppingState : public CharacterState {
public:
  DroppingState() = default;
  ~DroppingState() = default;
  DroppingState(Vector2 _friction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 friction;
  int frameDelay, frameDelayCounter, frameIndex;
};

#endif // CHARACTER_STATE_H
