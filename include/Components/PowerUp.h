#pragma once    

#include "Components/Component.h"
#include "raylib.h"

class PowerUpComponent : public Component {
public:
  PowerUpComponent();
  PowerUpComponent(bool _powerUp);
  ~PowerUpComponent();
  void setPowerUp(bool _powerUp);
  bool powerUp;
};