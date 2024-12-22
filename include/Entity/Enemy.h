// #pragma once
// #include "AbstractEntity.h"


// const float ENEMY_SPEED = 50.0f;

// class Enemy : public AbstractEntity {
// public:
//   Enemy() = default;
//   Enemy(std::string name);
//   virtual ~Enemy() = default;

// protected:
//   virtual void handleCollision() = 0;
// };


// class Goomba : public Enemy {
// public:
//   Goomba() = default;
//   Goomba(std::string name);
//   void update(float deltaTime) override;
//   void draw() override;

// private:
//   void handleCollision() override;
// };