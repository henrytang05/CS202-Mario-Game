#ifndef ENEMY_H
#define ENEMY_H
#include "EntityManager.h"
#include "TextureManager.h"
class Goomba : public AbstractEntity {
public:
  void changeState() override;
};

#endif // ENEMY_H
