#pragma once

#include "EntityManager.h"
#include "pch.h"
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <variant>
#include "Entity/EntityFactory.h"
#include "Components/Components_include.h"
#include "ScoreManager.h"
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

struct MarioJumpOnKoopa : public Event {
  MarioJumpOnKoopa(uint32_t player, uint32_t enemy)
    : MarioID(player), EnemyID(enemy) {}
  void handle() override;
  uint32_t MarioID;
  uint32_t EnemyID;
};
struct MarioLargeToSmall : public Event {
  MarioLargeToSmall(uint32_t player) : MarioID(player) {}
  void handle() override;
  uint32_t MarioID;
};//Event so that Mushroom can be created
struct PowerUpEvent : public Event {
  PowerUpEvent(Vector2 position) : position(position) {}
  void handle() override;
  Vector2 position;
};

struct CoinEvent : public Event {
  CoinEvent(Vector2 position) : position(position) {}
  void handle() override;
  Vector2 position;
};

struct CoinCollectEvent : public Event {
  CoinCollectEvent(uint32_t player, uint32_t coin) : MarioID(player), CoinID(coin) {}
  void handle() override;
  uint32_t MarioID, CoinID;
};

struct MarioSmallToLarge : public Event {
  MarioSmallToLarge(uint32_t player, uint32_t mushroom) : MarioID(player), MushroomID(mushroom) {}
  void handle() override;
  uint32_t MarioID, MushroomID;
};

struct FinishLevelEvent : public Event {
  FinishLevelEvent(uint32_t player) : MarioID(player) {}
  void handle() override;
  uint32_t MarioID;
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


struct MarioTouchRightKoopa : public Event {
  MarioTouchRightKoopa(uint32_t player, uint32_t enemy)
    : MarioID(player), EnemyID(enemy) {}
  void handle() override;
  uint32_t MarioID;
  uint32_t EnemyID;
};
