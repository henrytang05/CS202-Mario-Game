#ifndef SYSTEM_H
#define SYSTEM_H
#include "EntityComponent.h"
class System {
  friend class SystemManager;

public:
  virtual ~System() = 0;

  const std::set<Entity> GetEntities() const { return mEntities; }

private:
  std::set<Entity> mEntities;
};
inline System::~System() {}

#endif // SYSTEM_H
