#ifndef TAG_COMPONENT_H
#define TAG_COMPONENT_H

#include "Components/Component.h"
#include "GameObject.h"

class PlayerTag : public Component {};
class EnemyTag : public Component {};
class AITag : public Component {};
class PowerupTag : public Component {};
class CoinInBlockTag : public Component {
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(CoinInBlockTag, position_fixed.x,
                                 position_fixed.y)
public:
  CoinInBlockTag(Vector2 pos) : position_fixed(pos) {};
  CoinInBlockTag(float x, float y) : position_fixed({x, y}) {};
  CoinInBlockTag() : position_fixed({0, 0}) {};
  Vector2 position_fixed;
};
class CoinTag : public Component {};
class FlagTag : public Component {
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(FlagTag, position_fixed.x, position_fixed.y,
                                 triggered)
public:
  FlagTag(Vector2 pos) : position_fixed(pos) {};
  FlagTag(float x, float y) : position_fixed({x, y}) {};
  FlagTag() : position_fixed({0, 0}) {};
  Vector2 position_fixed;
  bool triggered = false;
};
class PipeTag : public Component {};

#endif // TAG_COMPONENT_H
