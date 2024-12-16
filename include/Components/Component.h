#ifndef COMPONENT_H
#define COMPONENT_H

class AbstractEntity;
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
  void setEntity(AbstractEntity *e);

private:
  virtual void init();

protected:
  AbstractEntity *entity;

public:
  const std::string name;
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
