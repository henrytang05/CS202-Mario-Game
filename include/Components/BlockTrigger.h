#ifndef BLOCKTRIGGER_H
#define BLOCKTRIGGER_H

#include "Components/Component.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "globals.h"

class TriggerBehaviour {
public:
  virtual TriggerBehaviour *trigger(AbstractEntity* entity, float deltaTime) = 0;
};

class TriggerBrokenBlockWhenHitBySmall : public TriggerBehaviour {
private:
  float sumFrame;
  Vector2 fixedPosition;

public:
  TriggerBrokenBlockWhenHitBySmall();
  TriggerBrokenBlockWhenHitBySmall(Vector2 _fixedPosition);
  TriggerBehaviour *trigger(AbstractEntity* entity, float deltaTime) override;
};

class TriggerBrokenBlockWhenHitByLarge : public TriggerBehaviour {
private:
  float sumFrame;
  Vector2 fixedPosition;

public:
  TriggerBrokenBlockWhenHitByLarge();
  TriggerBrokenBlockWhenHitByLarge(Vector2 _fixedPosition);
  TriggerBehaviour *trigger(AbstractEntity* entity, float deltaTime) override;
};

class TriggerQuestionBlock : public TriggerBehaviour {
private:
  float sumFrame;
  Vector2 fixedPosition;

public:
  TriggerQuestionBlock();
  TriggerQuestionBlock(Vector2 _fixedPosition);
  TriggerBehaviour *trigger(AbstractEntity* entity, float deltaTime) override;
};

class BlockTriggerComponent : public Component {
public:
  ~BlockTriggerComponent();
  BlockTriggerComponent();
  void init();
  void setTrigger(TriggerBehaviour *_trigger);
  void update(float deltaTime);

private:
  TriggerBehaviour *trigger;
};
#endif // BLOCKTRIGGER_H
