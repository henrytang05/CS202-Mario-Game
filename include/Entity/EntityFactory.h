#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "AbstractEntity.h"
#include "Entity/PlayableEntity.h"
#include "GameObject.h"
class IFactory {
public:
  virtual ~IFactory() = default;
  virtual Shared<Mario> createMario() = 0;
  virtual Shared<Luigi> createLuigi() = 0;
  virtual Shared<AbstractEntity> createGoomba() = 0;
  virtual Shared<AbstractEntity> createBlock(string type,Texture2D texture, Vector2 position) = 0;
};

class EntityFactory : public IFactory {
public:
  Shared<Mario> createMario() override;
  Shared<Luigi> createLuigi() override;
  Shared<AbstractEntity> createGoomba() override;
  Shared<AbstractEntity> createBlock(string type,Texture2D texture, Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
