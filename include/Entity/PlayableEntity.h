#ifndef PLAYABLE_ENTITY_H
#define PLAYABLE_ENTITY_H

#include "AbstractEntity.h"
#include "Entity/States/CharacterStates.h"
#include "Interface.h"

class PlayableEntity : public AbstractEntity,
                       public IInputable,
                       public IMovable {

public:
  PlayableEntity() = default;
  PlayableEntity(std::string name);

  virtual ~PlayableEntity() = default;
  Vector2 getVelocity() override;
  void setVelocity(Vector2 newVelocity) override;
};
class Luigi : public PlayableEntity {
public:
  Luigi();
  ~Luigi() = default;

  void update() override;
  void draw() override;

private:
  void input() override;
  Unique<CharacterState> state;
};
class Mario : public PlayableEntity {
public:
  Mario();
  ~Mario() = default;

  void update() override;
  void draw() override;

private:
  void input() override;
  Unique<CharacterState> state;
};

#endif // PLAYABLE_ENTITY_H
