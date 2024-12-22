#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "AbstractEntity.h"
#include "Entity/Enemy.h"
#include "Entity/Luigi.h"
#include "Entity/Mario.h"
#include "Entity/PlayableEntity.h"
#include "EntityManager.h"
#include "GameObject.h"
class IFactory {
public:
  map<string, Texture2D> mapTexture;
  virtual ~IFactory() = default;
  virtual AbstractEntity &createMario() = 0;
  virtual AbstractEntity &createLuigi() = 0;
  virtual AbstractEntity &createEnemy(Vector2 position, Vector2 size) = 0;
  virtual AbstractEntity &createGoomba() = 0;
  virtual AbstractEntity &createBlock(string type, Vector2 position) = 0;
  virtual AbstractEntity &createPipe(Vector2 position, Vector2 size) = 0;
  virtual AbstractEntity &createFlag(Vector2 position) = 0;
  virtual AbstractEntity &createFlagPole(Vector2 position) = 0;
};

class EntityFactory : public IFactory {
public:
  EntityFactory();
  AbstractEntity &createMario() override;
  AbstractEntity &createLuigi() override;
  AbstractEntity &createEnemy(Vector2 position, Vector2 size) override;

  AbstractEntity &createGoomba() override;
  AbstractEntity &createBlock(string type, Vector2 position) override;
  AbstractEntity &createPipe(Vector2 position, Vector2 size) override;
  AbstractEntity &createFlag(Vector2 position) override;
  AbstractEntity &createFlagPole(Vector2 position) override;

private:
  EntityManager &EM;
};

#endif // ENTITY_FACTORY_H
