#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/Enemy.h"
#include "Entity/Mario.h"
#include "Entity/PlayableEntity.h"
#include "EntityManager.h"
#include "GameObject.h"
#include "pch.h"

class IFactory {
public:
  std::map<std::string, Texture2D> mapTexture;
  IFactory(EntityManager &EM) : EM(EM) {}
  virtual ~IFactory() = default;
  virtual Shared<Coin> createCoin(Vector2 position) = 0;
  virtual Weak<AbstractEntity> createMario() = 0;
  virtual Weak<AbstractEntity> createLuigi() = 0;
  virtual Weak<AbstractEntity> createEnemy(Vector2 position, Vector2 size) = 0;
  virtual Weak<AbstractEntity> createGoomba(Vector2 position, Vector2 size) = 0;
  virtual Weak<AbstractEntity> createBlock(std::string type,
                                           Vector2 position) = 0;
  virtual Weak<Pipe> createPipe(Vector2 position, Vector2 size) = 0;
  virtual Weak<Flag> createFlag(Vector2 position) = 0;
  virtual Weak<FlagPole> createFlagPole(Vector2 position) = 0;
  virtual Weak<Piranha> createPiranha(Vector2 position) = 0;
  virtual Weak<Mushroom> createMushroom(Vector2 position) = 0;

protected:
  EntityManager &EM;
};

class EntityFactory : public IFactory {
public:
  EntityFactory(EntityManager &EM);
  Weak<AbstractEntity> createMario() override;
  Weak<AbstractEntity> createLuigi() override;
  Weak<AbstractEntity> createEnemy(Vector2 position, Vector2 size) override;

  Shared<Coin> createCoin(Vector2 position) override;
  Weak<AbstractEntity> createGoomba(Vector2 position, Vector2 size) override;
  Weak<AbstractEntity> createBlock(std::string type, Vector2 position) override;
  Weak<Pipe> createPipe(Vector2 position, Vector2 size) override;
  Weak<Flag> createFlag(Vector2 position) override;
  Weak<FlagPole> createFlagPole(Vector2 position) override;
  Weak<Piranha> createPiranha(Vector2 position) override;
  Weak<Mushroom> createMushroom(Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
