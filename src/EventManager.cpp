#include "EventManager.h"
#include "Components/Components_include.h"
#include "System/System.h"
#include "globals.h"
#include "pch.h"

void MarioDieEvent::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(marioID);
  ASSERT(!_mario.expired());

  auto mario = _mario.lock();
  if (mario->getComponent<CharacterStateComponent>().getState() == "DEATH")
    return;
  mario->removeComponent<CollisionComponent>();
  mario->removeComponent<BoundingBoxComponent>();
  mario->getComponent<CharacterStateComponent>().setEnumState("DEATH");
  mario->getComponent<CharacterStateComponent>().setSizeState("SMALL");
  mario->getComponent<TextureComponent>().changeState(mario->getComponent<CharacterStateComponent>().getCurrentState());
  mario->getComponent<TransformComponent>().setVelocity({0.0f, -240.0f});
  mario->getComponent<MarioSoundComponent>().PlayMarioDieEffect();
}
void MarioLargeToSmall::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);

  ASSERT(!_mario.expired());

  auto mario = _mario.lock();
  mario->getComponent<CharacterStateComponent>().setSizeState("SMALL");
  auto &velocity = mario->getComponent<TransformComponent>();
  auto &size = mario->getComponent<BoundingBoxComponent>();
  size.setSize({16.0f, 20.0f});
  velocity.x = 0.0f;
  mario->getComponent<TextureComponent>().changeState(mario->getComponent<CharacterStateComponent>().getCurrentState());
}
void MarioSmallToLarge::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);

  ASSERT(!_mario.expired());

  auto mario = _mario.lock();
  mario->getComponent<CharacterStateComponent>().setSizeState("LARGE");
  auto &velocity = mario->getComponent<TransformComponent>();
  auto &position = mario->getComponent<PositionComponent>();
  auto &size = mario->getComponent<BoundingBoxComponent>();
  size.setSize({16.0f, 28.0f});
  position.y -= 10.0f;
  velocity.x = 0.0f;
  mario->getComponent<TextureComponent>().changeState(mario->getComponent<CharacterStateComponent>().getCurrentState());
}
void MarioJumpOnGoomba::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);
  auto _goomba = EM.getEntityPtr(EnemyID);

  ASSERT(!_mario.expired());
  ASSERT(!_goomba.expired());

  auto mario = _mario.lock();
  auto goomba = _goomba.lock();
  goomba->getComponent<TextureComponent>().changeState("Die");
  goomba->getComponent<TransformComponent>().setVelocity({0.0f, 0.0f});
  mario->getComponent<CharacterStateComponent>().setEnumState("JUMPING");
  mario->getComponent<TransformComponent>().setVelocity({mario->getComponent<TransformComponent>().x, -180.0f});
}

void PowerUpEvent::handle() {
  EntityManager &EM = EntityManager::getInstance();
  Unique<IFactory> entityFactory;
  entityFactory = std::make_unique<EntityFactory>(EM);
  auto powerUp = entityFactory->createMushroom(Vector2{position.x, position.y - 16.0f});
}

void CoinEvent::handle() {
  EntityManager &EM = EntityManager::getInstance();
  Unique<IFactory> entityFactory;
  entityFactory = std::make_unique<EntityFactory>(EM);
  //auto coin = entityFactory->createCoin(Vector2{position.x, position.y+16.0f});
}

void EventQueue::pushEvent(Unique<Event> &e) { eventQueue.push(std::move(e)); }

void EventQueue::pushEvent(Unique<Event> e) { eventQueue.push(std::move(e)); }

void EventQueue::processAllEvents() {
  while (!eventQueue.empty()) {
    Unique<Event> event = std::move(eventQueue.front());
    eventQueue.pop();

    event->handle();
  }
}

void EventQueue::reset() {
  while (!eventQueue.empty()) {
    eventQueue.pop();
  }
}

EventQueue &EventQueue::getInstance() {
  static EventQueue instance;
  return instance;
}
