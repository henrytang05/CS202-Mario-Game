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

void MarioJumpOnKoopa::handle()
{
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);
  auto _koopa = EM.getEntityPtr(EnemyID);

  ASSERT(!_mario.expired());
  ASSERT(!_koopa.expired());

  auto mario = _mario.lock();
  auto koopa = _koopa.lock();
  if(koopa->getComponent<TextureComponent>().state == "Shell") {
      koopa->getComponent<TextureComponent>().changeState("Die");
      mario->getComponent<CharacterStateComponent>().setEnumState("JUMPING");
      mario->getComponent<TransformComponent>().setVelocity({mario->getComponent<TransformComponent>().x, -180.0f});
  }
  else { 
    koopa->getComponent<TextureComponent>().changeState("Shell");
    koopa->getComponent<BoundingBoxComponent>().setSize(Vector2{16,16});
    koopa->getComponent<PositionComponent>().setPosition(koopa->getComponent<PositionComponent>().getPosition() + Vector2{0,11});
    koopa->getComponent<TransformComponent>().setVelocity({0.0f, 0.0f});
    mario->getComponent<CharacterStateComponent>().setEnumState("JUMPING");
    mario->getComponent<TransformComponent>().setVelocity({mario->getComponent<TransformComponent>().x, -180.0f});
  }
}

void MarioTouchRightKoopa::handle()
{
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);
  auto _koopa = EM.getEntityPtr(EnemyID);

  ASSERT(!_mario.expired());
  ASSERT(!_koopa.expired());

  auto mario = _mario.lock();
  auto koopa = _koopa.lock();

  if(koopa->getComponent<TextureComponent>().state == "Shell") {
    koopa->getComponent<TextureComponent>().changeState("Shell-Moving");
    koopa->getComponent<TransformComponent>().setVelocity({ENEMY_SPEED * 2, 0.0f});
  }
  else {
    EventQueue& EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioDieEvent>(MarioID));
  }
}
