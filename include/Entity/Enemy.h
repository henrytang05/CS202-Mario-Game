#ifndef ENEMY_H
#define ENEMY_H
#include "AbstractEntity.h"
#include "Components/EnemyComponents.h"

const float ENEMY_SPEED = 50.0f;

class Enemy : public AbstractEntity {
public:
  Enemy() = default;
  Enemy(std::string name);
  void update(float deltatime) override;
  void draw() override;

private:
  void handleCollision();
};

#endif // ENEMY_H
