#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"
#include "TextureManager.h"
#include "Entity/EntityFactory.h"
#include "Observer.h"
#include "Components/BoundingBox.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Components/Transform.h"
#include "Components/BlockTrigger.h"
#include "Entity/Enemy.h"



// // Derived class for a normal block
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

// class Piranha : public AbstractEntity {
// public:
//   Piranha(Vector2 position);
//   ~Piranha() = default;
//   void update(float deltaTime) override;
//   void draw() override;

// private:
//   Vector2 position_fixed;
//   float elapsedTime=0;
// };

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