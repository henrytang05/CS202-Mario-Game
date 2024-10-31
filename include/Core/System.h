#ifndef SYSTEM_H
#define SYSTEM_H
#include "EntityComponent.h"
class System {
  friend class SystemManager;

public:
  virtual ~System() = default;

  const std::set<Entity> GetEntities() const { return mEntities; }

private:
  std::set<Entity> mEntities;
};

#endif // SYSTEM_H
