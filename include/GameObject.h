#pragma once

#include "EntityManager.h"
#include "Observer.h"
using json = nlohmann::json;

// typedef AbstractEntity GroundBlock;

Weak<AbstractEntity> createGroundBlock(Vector2 position);
Weak<AbstractEntity> createBrokenBlock(Vector2 position);
Weak<AbstractEntity> createHardBlock(Vector2 position);
Weak<AbstractEntity> createNormalBlock(Vector2 position);
Weak<AbstractEntity> createQuestionBlock(Vector2 position);

// Derived class for a pipe
class Pipe : public AbstractEntity {
private:
  bool isCollision = false;

public:
  Pipe(Vector2 position, Vector2 size);
  ~Pipe() = default;
  void init(Vector2 position, Vector2 size);
};

// Derived class for a flag
class Flag : public AbstractEntity {
private:
  bool isCollision = false;

public:
  Flag(Vector2 position);
  ~Flag() = default;
  void init(Vector2 position);
};

// Derived class for a flag pole
class FlagPole : public AbstractEntity {
private:
  bool isCollision = false;

public:
  FlagPole(Vector2 position);
  ~FlagPole() = default;
  void init(Vector2 position);
};




