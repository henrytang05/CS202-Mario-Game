#ifndef COMPONENT_H
#define COMPONENT_H
class Entity;
class Component;
using ComponentTypeID = std::size_t;

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {

public:
  Component();
  Component(std::string name);
  virtual ~Component();
  virtual void update();
  virtual void draw();
  void setEntity(Entity *e);

private:
  virtual void init();

public:
  const std::string name;

protected:
  Entity *entity;
};

inline ComponentTypeID getComponentTypeID() {
  static ComponentTypeID lastID = 0;
  return lastID++;
}

template <typename T> inline ComponentTypeID getComponentTypeID() noexcept {
  static ComponentTypeID typeID = getComponentTypeID();
  return typeID;
}

#endif // COMPONENT_H
