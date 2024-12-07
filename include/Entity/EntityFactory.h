#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Entity/Entity.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"

class IFactory {
public:
  virtual ~IFactory() = default;
  virtual Shared<Mario> createMario() = 0;
  virtual Shared<Entity> createLuigi() = 0;
  virtual Shared<Entity> createGoomba() = 0;
};

class EntityFactory : public IFactory {
public:
  Shared<Mario> createMario() override;
  Shared<Entity> createLuigi() override;
  Shared<Entity> createGoomba() override;
};

#endif // ENTITY_FACTORY_H
