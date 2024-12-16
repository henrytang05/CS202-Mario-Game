#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

class PlayableEntity;
const float WALKING_ACC = 0.1f;
const float RUNNING_ACC = 0.1f;
const float SKIDDING_DEC = 0.3f;
const float NORMAL_DEC = 0.3f;
const float JUMPPING_DEC = 5.0f;
const float JUMPING_ACC = 0.15f;
const float JUMPING_MOVING_ACC = 0.1f;
const float GRAVITY_DEC = 0.3f;
const float MAX_WALKING_VELO = 2.0f;
const float MAX_RUNNING_VELO = 3.0f;
const float MAX_JUMPING_VELO = 2.3f;
class EnumCharacterState {
private:
  enum FACING {
    RIGHT = 0,
    LEFT
  };
  enum STATE {
    IDLE = 0,
    MOVING,
    SKIDDING,
    JUMPING,
    DROPPING
  };
  enum SIZE {
    SMALL = 0,
    LARGE
  };
  STATE enumState;
  SIZE enumSize;
  FACING enumFacing;
public:
  EnumCharacterState() = default;
  EnumCharacterState(std::string _size, std::string _facing, std::string _state);
  virtual ~EnumCharacterState() = default;
  std::string getCurrentState();
  std::string getFacing();
  std::string getState();
  std::string getSize();
  void setEnumState(std::string newState);
  void setFacingState(std::string newFacing);
  void setSizeState(std::string newSize);
};
class CharacterState : public EnumCharacterState {
public:
  CharacterState() = default;
  CharacterState( std::string state, std::string facing, std::string size);
  virtual ~CharacterState() = default;
  virtual CharacterState *handleInput(PlayableEntity &character) = 0;
  virtual void update(PlayableEntity &character) = 0;
private:
  std::string stateTexture;
};

class StandingState : public CharacterState {
public:
  StandingState() = default;
  StandingState(Vector2 _friction, std::string size, std::string facing, std::string state);
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
  JumpingState(Vector2 _friction, std::string size, std::string facing, std::string state);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 friction;
};

class MovingState : public CharacterState {
public:
  MovingState() = default;
  ~MovingState() = default;
  MovingState(Vector2 _velocity, std::string size, std::string facing, std::string state);
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
  DroppingState(Vector2 _friction, std::string size, std::string facing, std::string state);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 friction;
  int frameDelay, frameDelayCounter, frameIndex;
};

#endif // CHARACTER_STATE_H
