#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER
#include "EntityComponent.h"

class EntityManager {
public:
  EntityManager();
  ~EntityManager();

  Entity CreateEntity();
  void DestroyEntity(Entity entity);
  Signature GetSignature(Entity entity);
  void SetSignature(Entity entity, Signature signature);

private:
  std::queue<Entity> mAvailableEntities;
  std::array<Signature, MAX_ENTITIES> mSignatures;

  uint32_t mLivingEntityCount;
};

// inline to avoid multiple definition error
inline EntityManager::EntityManager() : mLivingEntityCount(0) {
  for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
    mAvailableEntities.push(entity);
  }
}

inline EntityManager::~EntityManager() {}

inline Entity EntityManager::CreateEntity() {

  assert(mLivingEntityCount < MAX_ENTITIES &&
         "Too many entities in existence.");

  Entity id = mAvailableEntities.front();
  mAvailableEntities.pop();
  ++mLivingEntityCount;

  return id;
}

inline void EntityManager::DestroyEntity(Entity entity) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");

  mSignatures[entity].reset();

  mAvailableEntities.push(entity);
  --mLivingEntityCount;
}

inline Signature EntityManager::GetSignature(Entity entity) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");

  return mSignatures[entity];
}

inline void EntityManager::SetSignature(Entity entity, Signature signature) {
  assert(entity < MAX_ENTITIES && "Entity out of range.");
  mSignatures[entity] = signature;
}

#endif // ENTITY_MANAGER
