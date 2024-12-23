#pragma once

#include "EntityManager.h"
#include "Observer.h"
using json = nlohmann::json;

// Derived class for a normal block
class NormalBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  NormalBlock(Vector2 position);
  ~NormalBlock() = default;
  void init(Vector2 position);
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  BrokenBlock(Vector2 position);
  ~BrokenBlock() = default;
  void init(Vector2 position);
};

// Derived class for a hard block
class HardBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  HardBlock(Vector2 position);
  ~HardBlock() = default;
  void init(Vector2 position);
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  GroundBlock(Vector2 position);
  ~GroundBlock() = default;
  void init(Vector2 position);
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  QuestionBlock(Vector2 position);
  ~QuestionBlock() = default;
  void init(Vector2 position);
};

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

class Piranha : public AbstractEntity {
public:
  Piranha(Vector2 position);
  ~Piranha() = default;
  void init(Vector2 position);
};

class Mushroom : public AbstractEntity, public Observer {
public:
  Mushroom(Vector2 position);
  void init(Vector2 position);
  void onNotify() override;
  void update(float deltaTime) override;

private:
  bool isTriggered = false;
  float elapsedTime = 0;
  Vector2 position_fixed;
};
