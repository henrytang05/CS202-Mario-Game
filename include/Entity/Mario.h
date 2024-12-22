#ifndef MARIO_H
#define MARIO_H
#include "Entity/PlayableEntity.h"
class Mario : public PlayableEntity {
public:
  Mario();
  ~Mario() = default;
};

#endif // MARIO_H