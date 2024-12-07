#ifndef ENTITY_H
#define ENTITY_H

#include "AbstractEntity.h"
#include "CharacterState.h"
#include "Components/BoundingBox.h"
#include "Components/Component.h"
#include "Components/Position.h"
#include "Components/Transform.h"
#include "Interface.h"
#include "Logger.h"
#include "globals.h"

class Component;

class Entity : public IUpdatable,
               public AbstractEntity,
               public IDrawable,
               public IInputable {
public:
  Entity();
  Entity(std::string name);
  virtual ~Entity();

  void init();
  virtual void update() override;
  virtual void draw() override;

  virtual void setVelocity(Vector2 newVelocity) {
    getComponent<TransformComponent>().setVelocity(newVelocity);
  }
  virtual Vector2 getVelocity() {
    return getComponent<TransformComponent>().getVelocity();
  }
  virtual bool isOnTheGround() {
    return getComponent<BoundingBoxComponent>().isOnTheGround();
  }

public:
  std::string name;
  CharacterState *stateCharacter;
};

#endif // ENTITY_H
