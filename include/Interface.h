#ifndef INTERFACES_H
#define INTERFACES_H

class IIputable {
public:
  virtual ~IIputable() = default;
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

#endif // INTERFACES_H
