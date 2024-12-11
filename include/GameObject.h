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

  // GameObject(Vector2 pos) : position(pos) {}
  // virtual void Render() = 0;
  // void SetPosition(Vector2 pos) { position = pos; }
  // Vector2 GetPosition() const { return position; }
};

// Derived class for a block
class Block : public GameObject {
public:
    Block(Texture2D texture, Vector2 position);
    virtual ~Block(); // Add this line
    void draw() override;
    void update() override {
        // Implementation of the update function
    }
};

// Derived class for an interactable object
// class Interact : public GameObject {
//   Texture2D texture;

// public:
//   Interact(Texture2D tex, Vector2 pos) : GameObject(pos), texture(tex) {}
//   void Render() override;
// };
