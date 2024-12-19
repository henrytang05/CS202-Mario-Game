#ifndef PLAYABLE_ENTITY_H
#define PLAYABLE_ENTITY_H

#include "AbstractEntity.h"
#include "Entity/States/CharacterStates.h"
#include "Interface.h"
/*
        const MIN_WALK = 4.453125;
        const MAX_WALK = 93.75;
        const MAX_RUN = 153.75;
        const ACC_WALK = 133.59375;
        const ACC_RUN = 200.390625;
        const DEC_REL = 182.8125;
        const DEC_SKID = 365.625;
        const MIN_SKID = 33.75;

        const STOP_FALL = 1575;
        const WALK_FALL = 1800;
        const RUN_FALL = 2025;
        const STOP_FALL_A = 450;
        const WALK_FALL_A = 421.875;
        const RUN_FALL_A = 562.5;

        const MAX_FALL = 270;
*/
const float WALKING_ACC = 133.59375f;
const float RUNNING_ACC = 200.390625f;
const float NORMAL_DEC = 182.8125f;
const float SKIDDING_DEC = 365.625f;
const float MIN_SKIDDING = 33.75f;
const float GRAVITY_DEC = 562.0f;
const float MIN_WALKING_VELO = 4.453125f;
const float MAX_WALKING_VELO = 93.75f;
const float MAX_RUNNING_VELO = 153.75f;
const float JUMPING_VELO = -240.0f;
const float MAX_FALL = 270.0f;
const float FALL_ACC_A = 421.875f;
const float FALL_ACC = 1800.0f;
class PlayableEntity : public AbstractEntity,
                       public IInputable,
                       public IMovable {
private:
  float fallAcc;
  float timeFrameCounter;

public:
  PlayableEntity();
  PlayableEntity(std::string name);

  virtual void update(float deltaTime) override;

  virtual ~PlayableEntity() = default;
  Vector2 getVelocity() override;
  void setVelocity(Vector2 newVelocity) override;
  virtual void handleInput(Shared<CharacterState> &state, float deltaTime);
};
class Luigi : public PlayableEntity {
public:
  Luigi();
  ~Luigi() = default;

  void update(float deltaTime) override;
  void draw() override;

private:
  void input() override;
  Shared<CharacterState> state;
};
class Mario : public PlayableEntity {
public:
  Mario();
  ~Mario() = default;

  void update(float deltaTime) override;
  void draw() override;

private:
  void input() override;
  Shared<CharacterState> state;
};

#endif // PLAYABLE_ENTITY_H
