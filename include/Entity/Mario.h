#ifndef MARIO_H
#define MARIO_H

#include "EntityManager.h"
Weak<AbstractEntity> initMario();
Weak<AbstractEntity> initLuigi();
Weak<AbstractEntity> initGoomba(Vector2 position, Vector2 size);
Weak<AbstractEntity> initPiranha(Vector2 position);
#endif // MARIO_H
