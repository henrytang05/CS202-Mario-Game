#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "AbstractEntity.h"
#include "Entity/Enemy.h"
#include "Entity/PlayableEntity.h"
#include "Entity/Mario.h"
#include "Entity/Luigi.h"
#include "GameObject.h"
#include "Entity/Enemy.h"
class IFactory {
public:
  map<string, Texture2D> mapTexture;
  virtual ~IFactory() = default;
  virtual Shared<Mario> createMario() = 0;
  virtual Shared<Luigi> createLuigi() = 0;
  virtual Shared<Enemy> createEnemy(Vector2 position, Vector2 size) = 0;
  virtual Shared<AbstractEntity> createGoomba() = 0;
  virtual Shared<AbstractEntity> createBlock(string type, Vector2 position) = 0;
  virtual Shared<AbstractEntity> createPipe(Vector2 position, Vector2 size) = 0;
  virtual Shared<AbstractEntity> createFlag(Vector2 position) = 0;
  virtual Shared<AbstractEntity> createFlagPole(Vector2 position) = 0;
  virtual Shared<AbstractEntity> createPiranha(Vector2 position) = 0;
  virtual Shared<AbstractEntity> createMushroom(Vector2 position) = 0;
};

class EntityFactory : public IFactory {
public:
  Shared<Mario> createMario() override;
  Shared<Luigi> createLuigi() override;
  Shared<Enemy> createEnemy(Vector2 position, Vector2 size) override;

  Shared<AbstractEntity> createGoomba() override;
  Shared<AbstractEntity> createBlock(string type, Vector2 position) override;
  Shared<AbstractEntity> createPipe(Vector2 position, Vector2 size) override;
  Shared<AbstractEntity> createFlag(Vector2 position) override;
  Shared<AbstractEntity> createFlagPole(Vector2 position) override;
  Shared<AbstractEntity> createPiranha(Vector2 position) override;
  Shared<AbstractEntity> createMushroom(Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
