#ifndef INTERFACES_H
#define INTERFACES_H

class IInputable {
public:
  virtual ~IInputable() = default;
  virtual void input() = 0;
};

class IUpdatable {
public:
  virtual ~IUpdatable() = default;
  virtual void update() = 0;
};

class IDrawable {
public:
  virtual ~IDrawable() = default;
  virtual void draw() = 0;
};

class IMovable {
public:
  virtual ~IMovable() = default;
  virtual void setVelocity(Vector2 newVelocity) = 0;
  virtual Vector2 getVelocity() = 0;
};

class IConcreteEntity {
public:
  virtual ~IConcreteEntity() = default;
  virtual bool isOnTheGround() = 0;
};

#endif // INTERFACES_H
