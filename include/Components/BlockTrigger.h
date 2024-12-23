#ifndef BLOCKTRIGGER_H
#define BLOCKTRIGGER_H

#include "Components/Component.h"
#include "Components/Components_include.h"
#include "AbstractEntity.h"
#include "globals.h"


class TriggerBehaviour {
public:
    virtual TriggerBehaviour* trigger(AbstractEntity *entity, float deltaTime) = 0;
};

class TriggerBrokenBlockWhenHitBySmall : public TriggerBehaviour {
private:
    float sumFrame;
    Vector2 fixedPosition;
public:
    TriggerBrokenBlockWhenHitBySmall();
    TriggerBrokenBlockWhenHitBySmall(Vector2 _fixedPosition);
    TriggerBehaviour* trigger(AbstractEntity *entity, float deltaTime) override;
};

// class TriggerBrokenBlockWhenHitByLarge : public TriggerBehaviour {
// private:
//     float sumFrame;
// public:
//     TriggerBrokenBlockWhenHitByLarge();
//     TriggerBehaviour* trigger(AbstractEntity *entityy, float deltaTime) override;
// };

// class TriggerQuestionBlock : public TriggerBehaviour {
// private:
//     float sumFrame;
//     Vector2 fixedPosition;
// public:
//     TriggerQuestionBlock();
//     TriggerQuestionBlock(Vector2 _fixedPosition);
//     TriggerBehaviour* trigger(AbstractEntity *entity, float deltaTime) override;
// };

class TriggerCoin : public TriggerBehaviour {
private:
    float sumFrame;
    Vector2 fixedPosition;
public:
    TriggerCoin();
    TriggerCoin(Vector2 _fixedPosition);
    TriggerBehaviour* trigger(AbstractEntity *entity, float deltaTime) override;
};

class BlockTriggerComponent : public Component {
public:
  ~BlockTriggerComponent();
  BlockTriggerComponent();
  void init() override;
  void setTrigger(TriggerBehaviour *_trigger);
  void update(float deltaTime) override;
private:
    TriggerBehaviour *trigger;
};

#endif // BLOCKTRIGGER_H