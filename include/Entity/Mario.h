#ifndef MARIO_H
#define MARIO_H

#include "EntityManager.h"
Weak<AbstractEntity> initMario();
Weak<AbstractEntity> initLuigi();
Weak<AbstractEntity> initGoomba(Vector2 position, Vector2 size);

#endif // MARIO_H
