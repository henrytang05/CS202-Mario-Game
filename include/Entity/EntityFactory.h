#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/Enemy.h"
#include "Entity/Luigi.h"
#include "Entity/Mario.h"
#include "Entity/PlayableEntity.h"
#include "EntityManager.h"
#include "GameObject.h"
#include "pch.h"

// Derived class for a normal block
// class NormalBlock : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     NormalBlock() = default;
//     NormalBlock(Vector2 position);
//     ~NormalBlock() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a broken block
// class BrokenBlock : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     BrokenBlock() = default;
//     BrokenBlock(Vector2 position);
//     ~BrokenBlock() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a hard block
// class HardBlock : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     HardBlock() = default;
//     HardBlock(Vector2 position);
//     ~HardBlock() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a ground block
// class GroundBlock : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     GroundBlock() = default;
//     GroundBlock(Vector2 position);
//     ~GroundBlock() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a question block
// class QuestionBlock : public AbstractEntity{
// private:
//     bool isCollision = false;
// public:
//     QuestionBlock() = default;
//     QuestionBlock(Vector2 position);
//     ~QuestionBlock() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a pipe
// class Pipe : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     Pipe() = default;
//     Pipe(Vector2 position, Vector2 size);
//     ~Pipe() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a flag
// class Flag : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     Flag() = default;
//     Flag(Vector2 position);
//     ~Flag() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// // Derived class for a flag pole
// class FlagPole : public AbstractEntity {
// private:
//     bool isCollision = false;
// public:
//     FlagPole() = default;
//     FlagPole(Vector2 position);
//     ~FlagPole() = default;
//     void draw() override;
//     void update(float deltaTime) override;
// };
//
// class Piranha : public AbstractEntity {
// public:
//   Piranha(Vector2 position);
//   ~Piranha() = default;
//   void update(float deltaTime) override;
//   void draw() override;
//
// private:
//   Vector2 position_fixed;
//   float elapsedTime=0;
// };
//
// class Mushroom : public AbstractEntity, public Observer {
// public:
//   Mushroom() = default;
//   Mushroom(Vector2 position);
//   void update(float deltatime) override;
//   void draw() override {};
//   void onNotify() override;
// private:
//   void handleCollision();
//   bool isTriggered = false;
//   float elapsedTime = 0;
//   Vector2 position_fixed;
// };

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

  virtual Weak<AbstractEntity> createPiranha(Vector2 position) = 0;
  virtual Weak<AbstractEntity> createMushroom(Vector2 position) = 0;

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
  Weak<AbstractEntity> createPiranha(Vector2 position) override;
  Weak<AbstractEntity> createMushroom(Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
