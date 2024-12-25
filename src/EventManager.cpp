#include "EventManager.h"
void handleMarioJumpOnGoomba(const Event &event) {
  const auto &MJOG = std::get<MarioJumpOnGoombaEvent>(event.data);
  std::cout << "Mario (" << MJOG.marioID << ") jumped on Goomba ("
            << MJOG.goombaID << ").\n";
}

void handleUserClickButton(const Event &event) {
  const auto &UCB = std::get<UserClickButtonEvent>(event.data);
  std::cout << "User clicked button (" << UCB.buttonID << ").\n";
}

void EventQueue::registerHandler(EventType type,
                                 std::function<void(const Event &)> handler) {
  eventHandlers[type] = handler;
}

void EventQueue::pushEvent(const Event &event) { eventQueue.push(event); }

void EventQueue::processAllEvents() {
  while (!eventQueue.empty()) {
    Event event = eventQueue.front();
    eventQueue.pop();

    EventType type = event.type;
    eventHandlers[type](event);
  }
}

void produceEvents(EventQueue &eventQueue) {
  eventQueue.pushEvent(
      Event(EventType::MarioJumpOnGoomba, MarioJumpOnGoombaEvent({1, 2})));
  eventQueue.pushEvent(
      Event(EventType::UserClickButton, UserClickButtonEvent({1})));
}

void EventQueue::reset() { eventQueue = std::queue<Event>(); }

EventQueue &EventQueue::getInstance() {
  static EventQueue instance;
  return instance;
}
