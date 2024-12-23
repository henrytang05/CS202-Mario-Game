#pragma once
#include "pch.h"
#include "raylib.h"
using json = nlohmann::json;

#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "EntityManager.h"
#include "TextureManager.h"
// Factory class for creating entities

// Derived class for a normal block
class NormalBlock : public AbstractEntity {
private:
  bool isCollision = false;

public:
  NormalBlock(Vector2 position, EntityManager *EM = nullptr);
  ~NormalBlock() = default;
  void init(Vector2 position);
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity {
private:
  bool isCollision = false;

  void init(Vector2 position);

public:
  BrokenBlock() = default;
  BrokenBlock(Vector2 position, EntityManager *EM = nullptr);
  ~BrokenBlock() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a hard block
class HardBlock : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position);

public:
  HardBlock(Vector2 position, EntityManager *EM = nullptr);
  ~HardBlock() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position);

public:
  GroundBlock() = default;
  GroundBlock(Vector2 position, EntityManager *EM = nullptr);
  ~GroundBlock() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position);

public:
  QuestionBlock(Vector2 position, EntityManager *EM = nullptr);
  ~QuestionBlock() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a pipe
class Pipe : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position, Vector2 size);

public:
  Pipe() = default;
  Pipe(Vector2 position, Vector2 size, EntityManager *EM = nullptr);
  ~Pipe() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a flag
class Flag : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position);

public:
  Flag() = default;
  Flag(Vector2 position, EntityManager *EM = nullptr);
  ~Flag() = default;
  void draw() override;
  void update(float deltaTime) override;
};

// Derived class for a flag pole
class FlagPole : public AbstractEntity {
private:
  bool isCollision = false;
  void init(Vector2 position);

public:
  FlagPole() = default;
  FlagPole(Vector2 position, EntityManager *EM = nullptr);
  ~FlagPole() = default;
  void draw() override;
  void update(float deltaTime) override;
};
