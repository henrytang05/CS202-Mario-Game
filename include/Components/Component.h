#ifndef COMPONENT_H
#define COMPONENT_H

class EntityManager;
class AbstractEntity;

class Component {
public:
  Component(std::string name = "Unnamed", AbstractEntity *e = nullptr,
            EntityManager *em = nullptr);
  virtual ~Component();

  void setEntity(AbstractEntity *e);
  void setEntityManager(EntityManager *em);
  std::string getName() const;

protected:
  AbstractEntity *entity; // this is only a reference, dont delete
  EntityManager *EM;      // this is only a reference, dont delete
  std::string name;
};

struct SwingComponent : public Component {
  SwingComponent(Vector2 position_fixed = {0, 0}, float elapsedTime = 0)
      : Component("SwingComponent") {
    this->position_fixed = position_fixed;
    this->elapsedTime = elapsedTime;
  }
  ~SwingComponent() = default;
  Vector2 position_fixed;
  float elapsedTime = 0;
};
#endif // COMPONENT_H
