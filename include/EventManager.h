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

struct MarioJumpOnGoomba : public Event {
  MarioJumpOnGoomba(uint32_t player, uint32_t enemy)
      : MarioID(player), EnemyID(enemy) {}
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
