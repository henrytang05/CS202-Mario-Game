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

class StandingState : public CharacterState {
public:
  StandingState() = default;
  StandingState(Vector2 _fraction);
  ~StandingState() = default;
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
};

class JumpingState : public CharacterState {
public:
  JumpingState() = default;
  ~JumpingState() = default;
  JumpingState(Vector2 _fraction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
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
  DroppingState(Vector2 _fraction);
  CharacterState *handleInput(PlayableEntity &character) override;
  void update(PlayableEntity &character) override;

private:
  Vector2 fraction;
  int frameDelay, frameDelayCounter, frameIndex;
};

#endif // CHARACTER_STATE_H
