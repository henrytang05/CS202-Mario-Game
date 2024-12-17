#ifndef ENEMY_H
#define ENEMY_H
#include "AbstractEntity.h"
#include "Components/EnemyComponents.h"

class Enemy : public AbstractEntity {
public:
  Enemy() = default;
  Enemy(std::string name);
  void update() override;
  void draw() override;
};

#endif // ENEMY_H
