#pragma once

#include "EntityManager.h"
#include "pch.h"
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <variant>

struct Event {
  virtual void handle() = 0;
};

struct MarioDieEvent : public Event {
  MarioDieEvent(uint32_t marioID) : marioID(marioID) {}
  void handle() override;
  uint32_t marioID;
};

struct PlayerEnemyCollisionEvent : public Event {
  PlayerEnemyCollisionEvent(Weak<AbstractEntity> player,
                            Weak<AbstractEntity> enemy)
      : player(player), enemy(enemy) {}
  void handle() override;
  Weak<AbstractEntity> player;
  Weak<AbstractEntity> enemy;
};

struct MarioJumpOnGoomba : public Event {
  void handle() override;
  uint32_t MarioID;
  uint32_t EnemyID;
};

class EventQueue {
public:
  void pushEvent(Unique<Event> &e);
  void pushEvent(Unique<Event> e);
  void processAllEvents();
  void reset();
  static EventQueue &getInstance();

private:
  EventQueue() = default;
  EventQueue(const EventQueue &) = delete;
  EventQueue &operator=(const EventQueue &) = delete;

private:
  std::queue<Unique<Event>> eventQueue;
};
