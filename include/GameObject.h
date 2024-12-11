#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"
// Base class for all objects
class GameObject : public AbstractEntity,
                   public IDrawable {

public:
  GameObject() = default;
  GameObject(std::string name);

  virtual ~GameObject() = default;
};

// Derived class for a block
class Block : public GameObject {
public:
    Block(Texture2D texture, Vector2 position);
    virtual ~Block();
    void draw() override;
    void update() override;
};
