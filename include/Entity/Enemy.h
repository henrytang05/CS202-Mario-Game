#ifndef ENEMY_H
#define ENEMY_H
#include "EntityManager.h"

class Enemy : public AbstractEntity {
public:
  Enemy(std::string name = "Enemy");
  void changeState() override;
};
//
class Koomba : public Enemy {
public:
  Koomba(Vector2 position, Vector2 size);
  void changeState() override;
};

Weak<Koomba> initKoopa(Vector2 position, Vector2 size);

#endif // ENEMY_H
