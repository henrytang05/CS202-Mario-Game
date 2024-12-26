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
    koopa->modifyComponent<TextureComponent>();
    koopa->getComponent<TextureComponent>().addTexture("Shell", LoadTexture("./assets/Koopa/Shell-Koopa-Idle.png"));
    koopa->getComponent<TextureComponent>().addTexture("Die", LoadTexture("./assets/Koopa/Shell-Koopa-Idle.png"));
    std::vector<Texture2D> textures;
    textures.push_back(LoadTexture("./assets/Koopa/Shell-Koopa-Idle.png"));
    textures.push_back(LoadTexture("./assets/Koopa/Shell-Koopa-Moving.png"));
    textures.push_back(LoadTexture("./assets/Koopa/Shell-Koopa-Moving2.png"));
    koopa->getComponent<TextureComponent>().addTexture("Left-Moving", textures);
    std::reverse(textures.begin(), textures.end());
    koopa->getComponent<TextureComponent>().addTexture("Right-Moving", textures);
    koopa->removeComponent<EnemyTag>();
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

  if(koopa->getComponent<TextureComponent>().state == "Left-Moving" || koopa->getComponent<TextureComponent>().state == "Right-Moving") {
    if(mario->getComponent<CharacterStateComponent>().getSize() == "LARGE") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioLargeToSmall>(MarioID));
    }
  }
}
