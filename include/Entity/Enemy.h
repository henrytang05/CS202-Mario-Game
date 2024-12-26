#ifndef ENEMY_H
#define ENEMY_H
#include "EntityManager.h"

Weak<AbstractEntity> initGoomba(Vector2 position, Vector2 size);
Weak<AbstractEntity> initKoopa(Vector2 position, Vector2 size);
Weak<AbstractEntity> initPiranha(Vector2 position);
#endif // ENEMY_H
