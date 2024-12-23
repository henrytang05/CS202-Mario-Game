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

#endif // COMPONENT_H
