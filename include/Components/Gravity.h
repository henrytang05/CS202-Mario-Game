#ifndef GRAVITY_H
#define GRAVITY_H
#include "Components/Component.h"
class Gravity : public Component {
public:
  Gravity();
  void init() override;
  void setGravity(float newGravity);
  float getGravity() const;
  operator float() const;

private:
  float g;
};
#endif // GRAVITY_H
