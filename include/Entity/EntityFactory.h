#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "AbstractEntity.h"
#include "Entity/PlayableEntity.h"
#include "GameObject.h"
class IFactory {
public:
  virtual ~IFactory() = default;
  virtual Shared<Mario> createMario() = 0;
  virtual Shared<AbstractEntity> createLuigi() = 0;
  virtual Shared<AbstractEntity> createGoomba() = 0;
  virtual Shared<Block> createBlock() = 0;
};

class EntityFactory : public IFactory {
public:
  Shared<Mario> createMario() override;
  Shared<AbstractEntity> createLuigi() override;
  Shared<AbstractEntity> createGoomba() override;
  Shared<Block> createBlock() override;
};

#endif // ENTITY_FACTORY_H
