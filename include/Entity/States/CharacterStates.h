#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H
class CharacterState {
public:
  CharacterState() = default;
  CharacterState(std::string state, std::string facing, std::string size);
  ~CharacterState() = default;
  std::string getCurrentState();
  std::string getFacing();
  std::string getSize();
  std::string getState();
  void setEnumState(std::string newState);
  void setFacingState(std::string newFacing);
  void setSizeState(std::string newSize);

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
    DROPPING,
    DUCKLING, 
    DEATH
  };
  enum SIZE {
    SMALL = 0,
    LARGE
  };
  STATE enumState;
  SIZE enumSize;
  FACING enumFacing;
};
#endif // CHARACTER_STATE_H