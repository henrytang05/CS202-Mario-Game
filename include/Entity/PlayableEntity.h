#ifndef PLAYABLE_ENTITY_H
#define PLAYABLE_ENTITY_H

#include "Entity/Entity.h"
#include "Entity/States/CharacterStates.h"
#include "Interface.h"

class PlayableEntity : public Entity,
                       public IDrawable,
                       public IInputable,
                       public IMovable,
                       public IConcreteEntity {

public:
  PlayableEntity() = default;
  PlayableEntity(std::string name);

  virtual ~PlayableEntity() = default;
  Vector2 getVelocity() override;
  bool isOnTheGround() override;
  void setVelocity(Vector2 newVelocity) override;
};

class Mario : public PlayableEntity {
public:
  Mario();
  ~Mario() = default;

  void update() override;
  void draw() override;

private:
  void input() override;

private:
  Unique<CharacterState> state;
};

#endif // PLAYABLE_ENTITY_H
