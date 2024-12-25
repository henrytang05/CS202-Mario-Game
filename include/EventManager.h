#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <variant>

// Declare event data structures BEFORE using them in the variant
struct MarioJumpOnGoombaEvent {
  uint32_t marioID;
  uint32_t goombaID;
};

struct UserClickButtonEvent {
  int buttonID;
};
struct MarioDieEvent {
  uint32_t marioID;
};
enum class EventType { MarioJumpOnGoomba, UserClickButton, MarioDie };

using EventData = std::variant<MarioJumpOnGoombaEvent, UserClickButtonEvent, MarioDieEvent>;

struct Event {
  Event(EventType type, EventData data) : type(type), data(data) {}
  EventType type;
  EventData data;
};

void handleMarioJumpOnGoomba(const Event &event);

void handleUserClickButton(const Event &event);

class EventQueue {
public:
  void registerHandler(EventType type,
                       std::function<void(const Event &)> handler);
  //
  void pushEvent(const Event &event);
  void processAllEvents();
  void reset();
  static EventQueue &getInstance();

private:
  EventQueue() = default;
  EventQueue(const EventQueue &) = delete;
  EventQueue &operator=(const EventQueue &) = delete;

private:
  std::queue<Event> eventQueue;
  std::map<EventType, std::function<void(const Event &)>> eventHandlers;
};

void produceEvents(EventQueue &eventQueue);
