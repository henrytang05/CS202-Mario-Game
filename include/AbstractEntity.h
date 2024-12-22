#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include "Interface.h"
#include "Logger.h"
#include "pch.h"
#include <cstdint>

#define INVALID_ENTITY_ID -1

class AbstractEntity : public IUpdatable, public IDrawable {
public:
  AbstractEntity() : active(false), name("Unnamed") { id = (INVALID_ID); }

  AbstractEntity(uint32_t id, std::string name) : active(true), name(name) {
    this->id = id;
  }

  virtual ~AbstractEntity() {
#ifdef _DEBUG
    Log(name + " created: " + std::to_string(id));
#endif
  }

  uint32_t getId() const { return id; }
  bool operator==(const AbstractEntity &other) const { return id == other.id; }
  bool operator!=(const AbstractEntity &other) const { return id != other.id; }

  bool isActive() const { return active; }
  void destroy() { active = false; }

  // WARNING: This is a temporary solution
  void update(float dt) override {}
  void draw() override {}
  uint32_t getID() const { return id; }
  std::string getName() const { return name; }

private:
  bool active;
  uint32_t id;
  std::string name;
};

#endif // ABSTRACTENTITY_
