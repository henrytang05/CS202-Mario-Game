#pragma once
#include "Core/System.h"
#include "Core/EntityComponent.h"
class ScoreSystem: public System {
public:
    void tick() override;
    void onAddedToWorld() override;
private:
    std::vector<Entity> entities;
};