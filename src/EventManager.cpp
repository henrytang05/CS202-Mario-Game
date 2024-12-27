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
  ScoreManager::getInstance().resetScore();
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
  auto _mushroom = EM.getEntityPtr(MushroomID);

  ASSERT(!_mario.expired());
  ASSERT(!_mushroom.expired());

  auto mario = _mario.lock();
  auto mushroom = _mushroom.lock();
  mario->getComponent<CharacterStateComponent>().setSizeState("LARGE");
  auto &velocity = mario->getComponent<TransformComponent>();
  auto &position = mario->getComponent<PositionComponent>();
  auto &size = mario->getComponent<BoundingBoxComponent>();
  size.setSize({16.0f, 28.0f});
  position.y -= 10.0f;
  velocity.x = 0.0f;
  mario->getComponent<TextureComponent>().changeState(mario->getComponent<CharacterStateComponent>().getCurrentState());
  mushroom->getComponent<TextureComponent>().changeState("Die");
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
  ScoreManager::getInstance().addScore(1);
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
  auto coin = entityFactory->createCoin(Vector2{position.x, position.y - 10.0f});
  EM.getEntityRef(coin).addComponent<CoinInBlockTag>(position);
  EM.getEntityRef(coin).removeComponent<TransformComponent>();
  ScoreManager::getInstance().addScore(1);
}

void CoinCollectEvent::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);
  auto _coin = EM.getEntityPtr(CoinID);

  ASSERT(!_mario.expired());
  ASSERT(!_coin.expired());

  auto mario = _mario.lock();
  auto coin = _coin.lock();
  coin->destroy();
  mario->getComponent<MarioSoundComponent>().PlayCoinEffect();
  ScoreManager::getInstance().addScore(1);
}

void FinishLevelEvent::handle() {
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MarioID);

  ASSERT(!_mario.expired());

  auto mario = _mario.lock();
  mario->getComponent<TransformComponent>().setVelocity({50.0f, 0.0f});
  mario->getComponent<MarioSoundComponent>().PlayStageClearEffect();
  mario->removeComponent<PlayerTag>();
  
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

  if(koopa->getComponent<TextureComponent>().state == "Shell" || koopa->getComponent<TextureComponent>().state == "Shell-Moving") {
      koopa->getComponent<TextureComponent>().changeState("Die");
      koopa->getComponent<TransformComponent>().setVelocity({0.0f, 0.0f});
      mario->getComponent<CharacterStateComponent>().setEnumState("JUMPING");
      mario->getComponent<TransformComponent>().setVelocity({mario->getComponent<TransformComponent>().x, -180.0f});
      ScoreManager::getInstance().addScore(1);
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
    koopa->getComponent<TransformComponent>().setVelocity({ENEMY_SPEED * 3, 0.0f});
    mario->getComponent<PositionComponent>().setPosition(mario->getComponent<PositionComponent>().getPosition() + Vector2{-2,0});
  }
  else {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioDieEvent>(MarioID));
  }
}
