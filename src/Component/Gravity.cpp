#include "Components/Gravity.h"

Gravity::Gravity() : Component("Gravity"), g(1.0f) {}

void Gravity::init() {}

void Gravity::setGravity(float newGravity) { g = newGravity; }

float Gravity::getGravity() const { return g; }

Gravity::operator float() const { return g; }
