#pragma once
#include "Core/Coordinator.h"
class World: public Coordinator{
public:
    void Update() {
       UpdateAllSystem();
    }
    inline void UpdateAllSystem() {
  for (auto& s: mSystemManager->mSystems) {
    Shared<System>system = s.second;
    system->tick(this);
  }
}
};