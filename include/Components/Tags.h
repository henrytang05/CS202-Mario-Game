#ifndef TAG_COMPONENT_H
#define TAG_COMPONENT_H

#include "Components/Component.h"

class PlayerTag : public Component {};
class EnemyTag : public Component {};
class AITag : public Component {};
class PowerupTag : public Component {};
class CoinInBlockTag : public Component {
public:
    CoinInBlockTag(Vector2 pos) : position_fixed(pos) {} ;
    CoinInBlockTag(float x, float y) : position_fixed({x, y}) {} ;
    CoinInBlockTag() : position_fixed({0, 0}) {} ;
    Vector2 position_fixed;
};
//class CoinTag : public Component {};
#endif // TAG_COMPONENT_H
