#include "System/System.h"
#include "Components/Components_include.h"
void BlockSystem::update(float dt) {
    EntityManager &EM = EntityManager::getInstance();
    auto Entities = EM.getHasAll<BlockTriggerComponent>();
    for (auto tEntity : Entities) {
        if(tEntity.expired()) continue;
        auto entity = tEntity.lock();
        entity->getComponent<BlockTriggerComponent>().update(dt);
    }
}