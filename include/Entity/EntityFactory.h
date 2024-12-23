#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include "AbstractEntity.h"
#include "Entity/Enemy.h"
#include "Components/BoundingBox.h"
#include "Components/Collision.h"
#include "Components/Components_include.h"
#include "Components/EnemyComponents.h"
#include "Components/Gravity.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Entity/Luigi.h"
#include "Entity/Mario.h"
#include "Entity/PlayableEntity.h"
#include "pch.h"

// Derived class for a normal block
class NormalBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    NormalBlock() = default;
    NormalBlock(Vector2 position);
    ~NormalBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    BrokenBlock() = default;
    BrokenBlock(Vector2 position);
    ~BrokenBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a hard block
class HardBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    HardBlock() = default;
    HardBlock(Vector2 position);
    ~HardBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    GroundBlock() = default;
    GroundBlock(Vector2 position);
    ~GroundBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity{
private:
    bool isCollision = false;
public:
    QuestionBlock() = default;
    QuestionBlock(Vector2 position);
    ~QuestionBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a pipe
class Pipe : public AbstractEntity {
private:
    bool isCollision = false;
public:
    Pipe() = default;
    Pipe(Vector2 position, Vector2 size);
    ~Pipe() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a flag
class Flag : public AbstractEntity {
private:
    bool isCollision = false;
public:
    Flag() = default;
    Flag(Vector2 position);
    ~Flag() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a flag pole
class FlagPole : public AbstractEntity {
private:
    bool isCollision = false;
public:
    FlagPole() = default;
    FlagPole(Vector2 position);
    ~FlagPole() = default;
    void draw() override;
    void update(float deltaTime) override;
};

class Piranha : public AbstractEntity {
public:
  Piranha(Vector2 position);
  ~Piranha() = default;
  void update(float deltaTime) override;
  void draw() override;

private:
  Vector2 position_fixed;
  float elapsedTime=0;
};

class Mushroom : public AbstractEntity, public Observer {
public:
  Mushroom() = default;
  Mushroom(Vector2 position);
  void update(float deltatime) override;
  void draw() override {};
  void onNotify() override;
private:
  void handleCollision();
  bool isTriggered = false;
  float elapsedTime = 0;
  Vector2 position_fixed;
};

class Coin : public AbstractEntity, public Observer {
private:
    bool isTriggered = false;
    float elapsedTime = 0;
public:
    Coin() = default;
    Coin(Vector2 position);
    ~Coin() = default;
    void draw() override{};
    void update(float deltaTime) override;
    void onNotify() override;
};

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
  virtual Shared<Mushroom> createMushroom(Vector2 position) = 0;
  virtual Shared<Coin> createCoin(Vector2 position) = 0;
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
  Shared<Mushroom> createMushroom(Vector2 position) override;
  Shared<Coin> createCoin(Vector2 position) override;
};

#endif // ENTITY_FACTORY_H
