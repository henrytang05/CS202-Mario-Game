#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H
class CharacterState {
public:
  CharacterState() = default;
  CharacterState(std::string facing, std::string size);
  virtual ~CharacterState() = default;
  std::string getCurrentState();
  virtual std::string getFacing();
  virtual std::string getSize();
  virtual std::string getState() = 0;
  virtual void setFacingState(std::string newFacing);
  virtual void setSizeState(std::string newSize);
protected:
  enum FACING {
    RIGHT = 0,
    LEFT
  };
  enum STATE {
    IDLE = 0,
    MOVING,
    SKIDDING,
    JUMPING,
    DROPPING,
    DUCKLING, 
    DEATH
  };
  enum SIZE {
    SMALL = 0,
    LARGE
  };
  STATE enumState;
private:
  SIZE enumSize;
  FACING enumFacing;
};
class SkiddingState : public CharacterState {
public:
  SkiddingState() = default;
  ~SkiddingState() = default;
  SkiddingState(std::string size, std::string facing);
  std::string getState() override;
};
class StandingState : public CharacterState {
public:
  StandingState() = default;
  ~StandingState() = default;
  StandingState(std::string size, std::string facing);
  std::string getState() override;
};

class JumpingState : public CharacterState {
public:
  JumpingState() = default;
  ~JumpingState() = default;
  JumpingState(std::string size, std::string facing);
  std::string getState() override;
};

class MovingState : public CharacterState {
public:
  MovingState() = default;
  ~MovingState() = default;
  MovingState(std::string size, std::string facing);
  std::string getState() override;
};
class DroppingState : public CharacterState {
public:
  DroppingState() = default;
  ~DroppingState() = default;
  DroppingState(std::string size, std::string facing);
  std::string getState() override;
};

class DucklingState : public CharacterState {
public:
  DucklingState() = default;
  ~DucklingState() = default;
  DucklingState(std::string size, std::string facing);
  std::string getState() override;
};

class DeathState : public CharacterState {
public:
  DeathState() = default;
  ~DeathState() = default;
  DeathState(std::string size, std::string facing);
  std::string getState() override;
};
#endif // CHARACTER_STATE_H