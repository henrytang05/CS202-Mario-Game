#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

class PlayableEntity;
class CharacterState {
public:
  CharacterState() = default;
  virtual ~CharacterState() = default;
  virtual CharacterState *handleInput(PlayableEntity &character) = 0;
  virtual void update(PlayableEntity &character) = 0;
};

class NewStandingState : public CharacterState {
public:
  NewStandingState() = default;
  NewStandingState(Vector2 _fraction);
  ~NewStandingState() = default;
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
};

class NewJumpingState : public CharacterState {
public:
  NewJumpingState() = default;
  ~NewJumpingState() = default;
  NewJumpingState(Vector2 _fraction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
};

class NewMovingState : public CharacterState {
public:
  NewMovingState() = default;
  ~NewMovingState() = default;
  NewMovingState(Vector2 _velocity);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 velocity;
  int frameDelay, frameDelayCounter, frameIndex;
};

class NewDroppingState : public CharacterState {
public:
  NewDroppingState() = default;
  ~NewDroppingState() = default;
  NewDroppingState(Vector2 _fraction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
  int frameDelay, frameDelayCounter, frameIndex;
};

#endif // CHARACTER_STATE_H
