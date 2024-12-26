#include "Components/PowerUp.h"

PowerUpComponent::PowerUpComponent() : Component("PowerUpComponent"), powerUp(false) {}
PowerUpComponent::PowerUpComponent(bool _powerUp) : Component("PowerUpComponent"), powerUp(_powerUp) {}
PowerUpComponent::~PowerUpComponent() {}
void PowerUpComponent::setPowerUp(bool _powerUp) {
  powerUp = _powerUp;
}