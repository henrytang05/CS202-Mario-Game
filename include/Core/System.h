#ifndef SYSTEM_H
#define SYSTEM_H
#include "Core/World.h"
#include "EntityComponent.h"
class System {
  friend class SystemManager;

public:
  virtual ~System() = default;
  virtual void tick(World * world) = 0;
  virtual void onAddedToWorld(World * world) = 0;
  const std::set<Entity> GetEntities() const { return mEntities; }

protected:
  std::set<Entity> mEntities;
  Shared<World> world;
};

#endif // SYSTEM_H
