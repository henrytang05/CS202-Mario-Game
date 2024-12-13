#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"

// Derived class for a normal block
class NormalBlock : public AbstractEntity,
                    public IDrawable,
                    public IUpdatable {
public:
    NormalBlock()=default;
    NormalBlock(Texture2D texture, Vector2 position);
    ~NormalBlock()=default;
    void draw() override;
    void update() override;
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity,
                    public IDrawable,
                    public IUpdatable {
public:
    BrokenBlock()=default;
    BrokenBlock(Texture2D texture, Vector2 position);
    ~BrokenBlock()=default;
    void draw() override;
    void update() override;
};

// Derived class for a hard block
class HardBlock : public AbstractEntity,
                  public IDrawable,
                  public IUpdatable {
public:
    HardBlock()=default;
    HardBlock(Texture2D texture, Vector2 position);
    ~HardBlock()=default;
    void draw() override;
    void update() override;
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity,
                    public IDrawable,
                    public IUpdatable {
public:
    GroundBlock()=default;
    GroundBlock(Texture2D texture, Vector2 position);
    ~GroundBlock()=default;
    void draw() override;
    void update() override;
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity,
                      public IDrawable,
                      public IUpdatable {
public:
    QuestionBlock()=default;
    QuestionBlock(Texture2D texture, Vector2 position);
    ~QuestionBlock()=default;
    void draw() override;
    void update() override;
};
