#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Entity/Enemy.h"
#include "Entity/Mario.h"
#include "Entity/PlayableEntity.h"
#include "EntityManager.h"
#include "GameObject.h"
class IFactory {
public:
  std::map<std::string, Texture2D> mapTexture;
  IFactory(EntityManager &EM) : EM(EM) {}
  virtual ~IFactory() = default;
  virtual Weak<AbstractEntity> createMario() = 0;
  virtual Weak<AbstractEntity> createLuigi() = 0;
  virtual Weak<AbstractEntity> createEnemy(Vector2 position, Vector2 size) = 0;
  virtual Weak<AbstractEntity> createGoomba(Vector2 position, Vector2 size) = 0;
  virtual Weak<AbstractEntity> createBlock(std::string type,
                                           Vector2 position) = 0;
  virtual Weak<AbstractEntity> createPipe(Vector2 position, Vector2 size) = 0;
  virtual Weak<AbstractEntity> createFlag(Vector2 position) = 0;
  virtual Weak<AbstractEntity> createFlagPole(Vector2 position) = 0;

protected:
  EntityManager &EM;
};

class EntityFactory : public IFactory {
public:
  EntityFactory(EntityManager &EM);
  Weak<AbstractEntity> createMario() override;
  Weak<AbstractEntity> createLuigi() override;
  Weak<AbstractEntity> createEnemy(Vector2 position, Vector2 size) override;

  Weak<AbstractEntity> createGoomba(Vector2 position, Vector2 size) override;
  Weak<AbstractEntity> createBlock(std::string type, Vector2 position) override;
  Weak<AbstractEntity> createPipe(Vector2 position, Vector2 size) override;
  Weak<AbstractEntity> createFlag(Vector2 position) override;
  Weak<AbstractEntity> createFlagPole(Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
