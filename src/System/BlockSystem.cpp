#include "Components/Components_include.h"
#include "System/System.h"
#include "globals.h"
void BlockSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<BlockTriggerComponent>();
  for (auto tEntity : Entities) {
    if (tEntity.expired())
      continue;
    auto entity = tEntity.lock();
    auto &blocktrigger = entity->getComponent<BlockTriggerComponent>();
    blocktrigger.update(dt);
  }
}
