#pragma once
#include "Core/World.h"
#include "Core/System.h"
#include "Components.h"

class AnimationSystem : public System {

public:
    void onAddedToWorld(World* world) override;

    void tick(World* world) override;

    ~AnimationSystem() override = default;
};