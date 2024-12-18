#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"
#include "Components/Position.h"
#include "Components/BoundingBox.h"
#include "Components/Texture.h"
#include "TextureManager.h"
// Factory class for creating entities

// Derived class for a normal block
class NormalBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    NormalBlock() = default;
    NormalBlock(Vector2 position);
    ~NormalBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a broken block
class BrokenBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    BrokenBlock() = default;
    BrokenBlock(Vector2 position);
    ~BrokenBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a hard block
class HardBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    HardBlock() = default;
    HardBlock(Vector2 position);
    ~HardBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a ground block
class GroundBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    GroundBlock() = default;
    GroundBlock(Vector2 position);
    ~GroundBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a question block
class QuestionBlock : public AbstractEntity {
private:
    bool isCollision = false;
public:
    QuestionBlock() = default;
    QuestionBlock(Vector2 position);
    ~QuestionBlock() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a pipe
class Pipe : public AbstractEntity {
private:
    bool isCollision = false;
public:
    Pipe() = default;
    Pipe(Vector2 position, Vector2 size);
    ~Pipe() = default;
    void draw() override;
    void update(float deltaTime) override;
};

// Derived class for a flag
class Flag : public AbstractEntity {
private:
    bool isCollision = false;
public:
    Flag() = default;
    Flag(Vector2 position);
    ~Flag() = default;
    void draw() override;
    void update(float deltaTime) override;
};