#pragma once

#include "Components/Component.h"
#include "Components/Position.h"
#include "raylib.h"

class PowerUpComponent : public Component {
public:
  PowerUpComponent();
  PowerUpComponent(bool _powerUp);
  ~PowerUpComponent();
  void setPowerUp(bool _powerUp);
  bool powerUp;

  void to_json(json &j) const override;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PowerUpComponent, powerUp)
