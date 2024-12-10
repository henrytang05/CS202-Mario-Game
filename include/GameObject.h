#pragma once
#include "pch.h"
using json = nlohmann::json;
#include "AbstractEntity.h"
// Base class for all objects
class GameObject {
protected:
  Vector2 position;

public:
  GameObject(Vector2 pos) : position(pos) {}
  virtual void Render() = 0;
  void SetPosition(Vector2 pos) { position = pos; }
  Vector2 GetPosition() const { return position; }
};

// Derived class for a block
class Block : public GameObject {
  Texture2D texture;

public:
  Block(Texture2D tex, Vector2 pos) : GameObject(pos), texture(tex) {}
  void Render() override;
};

// Derived class for an interactable object
class Interact : public GameObject {
  Texture2D texture;

public:
  Interact(Texture2D tex, Vector2 pos) : GameObject(pos), texture(tex) {}
  void Render() override;
};
