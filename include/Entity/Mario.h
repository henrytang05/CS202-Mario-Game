#ifndef MARIO_H
#define MARIO_H

#include "EntityManager.h"
Weak<AbstractEntity> initMario(EntityManager &EM);
Weak<AbstractEntity> initLuigi(EntityManager &EM);
Weak<AbstractEntity> initGoomba(EntityManager &EM, Vector2 position,
                                Vector2 size);

#endif // MARIO_H
