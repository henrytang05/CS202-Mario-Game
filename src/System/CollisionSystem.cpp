#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Tags.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "System/System.h"

void CollisionSystem::reset(CollisionComponent &cc) {
  for (int i = 0; i < 4; i++)
    cc.contact[i].reset();
}

void CollisionSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<CollisionComponent, PositionComponent,
                               BoundingBoxComponent>();
  auto otherEntities = EM.getHasAll<BoundingBoxComponent>();
  for (auto tEntity : Entities) {
    if (tEntity.expired())
      throw std::runtime_error("Entity is expired");
    
    if(tEntity.lock()->isActive() == false) continue;
    auto entity = tEntity.lock();
    std::vector<std::pair<int, float>> col;
    float t = 0, min_t = INFINITY;
    Vector2 cp, cn;
    for (int i = 0; i < (int)otherEntities.size(); i++) {
      if (*otherEntities[i].lock() == *entity)
        continue;
      Vector2 position = otherEntities[i]
                             .lock()
                             ->getComponent<PositionComponent>()
                             .getPosition();
      Vector2 size = otherEntities[i].lock()->getComponent<BoundingBoxComponent>().getSize();
      Vector2 velo = {0.0f, 0.0f};
      if (otherEntities[i].lock()->hasComponent<TransformComponent>())
        velo = otherEntities[i]
                   .lock()
                   ->getComponent<TransformComponent>()
                   .getVelocity();
      Rectangle bbOtherEntity =(Rectangle){position.x, position.y, size.x, size.y};
      if(otherEntities[i].lock()->hasComponent<CoinTag>()) 
        bbOtherEntity =(Rectangle){position.x + 8.0f, position.y + 8.0f, size.x, size.y};
      if (DynamicRectVsRect(dt, bbOtherEntity, cp, cn, t, entity, velo)) {
        col.push_back(std::make_pair(i, t));
      }
    }
    std::sort(
        col.begin(), col.end(),
        [&](const std::pair<int, float> &x, const std::pair<int, float> &y) {
          return x.second < y.second;
        });
    for (auto x : col)
      ResolveDynamicRectVsRect(dt, otherEntities[x.first], entity);
  }
}

bool CollisionSystem::ResolveDynamicRectVsRect(const float deltaTime,
                                               Weak<AbstractEntity> r_static,
                                               Weak<AbstractEntity> entity) {
  CollisionComponent &cc = entity.lock()->getComponent<CollisionComponent>();
  Vector2 contact_point, contact_normal;
  float contact_time = 0.0f;

  Vector2 position =
      r_static.lock()->getComponent<PositionComponent>().getPosition();
  Vector2 size =
      r_static.lock()->getComponent<BoundingBoxComponent>().getSize();
  Vector2 velo = {0.0f, 0.0f};
  if (r_static.lock()->hasComponent<TransformComponent>())
    velo = r_static.lock()->getComponent<TransformComponent>().getVelocity();
  Rectangle bbOtherEntity = (Rectangle){position.x, position.y, size.x, size.y};
  if(r_static.lock()->hasComponent<CoinTag>()) 
    bbOtherEntity =(Rectangle){position.x + 8.0f, position.y + 8.0f, size.x, size.y};
  if (DynamicRectVsRect(deltaTime, bbOtherEntity, contact_point, contact_normal,
                        contact_time, entity, velo)) {
    if (contact_normal.y > 0.0f)
      cc.contact[0] = r_static;

    if (contact_normal.x < 0.0f)
      cc.contact[1] = r_static;

    if (contact_normal.y < 0.0f)
      cc.contact[2] = r_static;

    if (contact_normal.x > 0.0f)
      cc.contact[3] = r_static;
    Vector2 velocity =
        entity.lock()->getComponent<TransformComponent>().getVelocity();
    
    if(r_static.lock()->hasComponent<CoinTag>() == false)
      velocity = velocity + (Vector2){contact_normal.x * std::fabs(velocity.x) *
                                          (1 - contact_time),
                                      contact_normal.y * std::fabs(velocity.y) *
                                          (1 - contact_time)};
    entity.lock()->getComponent<TransformComponent>().setVelocity(velocity);
    return true;
  }
  return false;
}
bool CollisionSystem::DynamicRectVsRect(
    const float deltaTime, const Rectangle &r_static, Vector2 &contact_point,
    Vector2 &contact_normal, float &contact_time, Weak<AbstractEntity> _entity,
    Vector2 secondVelo) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");
  auto entity = _entity.lock();
  Vector2 velocity = entity->getComponent<TransformComponent>().getVelocity();
  Vector2 size = entity->getComponent<BoundingBoxComponent>().getSize();
  Vector2 position = entity->getComponent<PositionComponent>().getPosition();
  velocity = (Vector2){velocity.x - secondVelo.x, velocity.y - secondVelo.y};
  if (velocity.x == 0 && velocity.y == 0)
    return false;

  // Expand target rectangle by source dimensions
  Rectangle expanded_target;
  expanded_target.x = r_static.x - size.x / 2.0f;
  expanded_target.y = r_static.y - size.y / 2.0f;
  expanded_target.width = r_static.width + size.x;
  expanded_target.height = r_static.height + size.y;
  Vector2 ray_origin =
      (Vector2){position.x + size.x / 2.0f, position.y + size.y / 2.0f};
  Vector2 ray_dir = (Vector2){velocity.x * deltaTime, velocity.y * deltaTime};
  if (RayVsRect(ray_origin, ray_dir, expanded_target, contact_point,
                contact_normal, contact_time))
    return (contact_time >= 0.0f && contact_time < 1.0f);
  else
    return false;
}
bool RayVsRect(const Vector2 &ray_origin, const Vector2 &ray_dir,
               const Rectangle &target, Vector2 &contact_point,
               Vector2 &contact_normal, float &t_hit_near) {
  contact_normal = {0, 0};
  contact_point = {0, 0};

  // Cache division
  Vector2 invdir = (Vector2){1.0f / ray_dir.x, 1.0f / ray_dir.y};

  // Calculate intersections with rectangle bounding axes
  Vector2 t_near = (Vector2){(target.x - ray_origin.x) * invdir.x,
                             (target.y - ray_origin.y) * invdir.y};
  Vector2 t_far =
      (Vector2){(target.x + target.width - ray_origin.x) * invdir.x,
                (target.y + target.height - ray_origin.y) * invdir.y};

  if (std::isnan(t_far.y) || std::isnan(t_far.x))
    return false;
  if (std::isnan(t_near.y) || std::isnan(t_near.x))
    return false;

  // Sort distances
  if (t_near.x > t_far.x)
    std::swap(t_near.x, t_far.x);
  if (t_near.y > t_far.y)
    std::swap(t_near.y, t_far.y);

  // Early rejection
  if (t_near.x > t_far.y || t_near.y > t_far.x)
    return false;

  // Closest 'time' will be the first contact
  t_hit_near = std::max(t_near.x, t_near.y);

  // Furthest 'time' is contact on opposite side of target
  float t_hit_far = std::min(t_far.x, t_far.y);

  // Reject if ray direction is pointing away from object
  if (t_hit_far < 0)
    return false;

  // Contact point of collision from parametric line equation
  contact_point =
      ray_origin + (Vector2){t_hit_near * ray_dir.x, t_hit_near * ray_dir.y};

  if (t_near.x > t_near.y)
    if (invdir.x < 0)
      contact_normal = {1, 0};
    else
      contact_normal = {-1, 0};
  else if (t_near.x < t_near.y) {
    if (invdir.y < 0)
      contact_normal = {0, 1};
    else
      contact_normal = {0, -1};
  }

  // Note if t_near == t_far, collision is principly in a diagonal
  // so pointless to resolve. By returning a CN={0,0} even though its
  // considered a hit, the resolver wont change anything.
  return true;
}

void CollisionHandlingSystem::update(float dt) {
  EntityManager &EM = EntityManager::getInstance();
  auto Entities = EM.getHasAll<CollisionComponent, PositionComponent,
                               BoundingBoxComponent, TransformComponent>();

  for (auto &_entity : Entities) {
    if (_entity.expired())
      throw std::runtime_error("Entity is expired");

    auto entity = _entity.lock();
    
    if (entity->isActive() &&entity->hasComponent<PlayerTag>()) {
      handlePlayerCollision(entity);
    }
    if(entity->isActive() && entity->hasComponent<PowerupTag>()) {
      handlePowerupCollision(entity);
    }
    if (entity->isActive() &&entity->hasComponent<EnemyTag>()) {
      handleEnemyCollision(entity);
    }
    if (entity->isActive() &&entity->hasComponent<AITag>()) {
      handleAICollision(entity);
    }
    if(entity->isActive())
      entity->getComponent<CollisionComponent>().reset();
  }
}
void CollisionHandlingSystem::handlePlayerCollision(Weak<AbstractEntity> _entity) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");
  auto entity = _entity.lock();
  auto &cc = entity->getComponent<CollisionComponent>();
  auto &tf = entity->getComponent<TransformComponent>();
  // Below Collision
  if (cc.getBelow().lock() == nullptr) {
    entity->getComponent<CharacterStateComponent>().setEnumState("DROPPING");
    if (entity->getComponent<PositionComponent>().y > screenHeight * 1.2f) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
    }
  } 
  else {
    auto below = entity->getComponent<CollisionComponent>().getBelow();
    if (cc.getBelow().lock()->hasComponent<EnemyTag>()) {
      if (!below.expired()) {
        auto belowEntity = below.lock();
        if (belowEntity->getName() == "Goomba") {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioJumpOnGoomba>(entity->getID(), belowEntity->getID()));
        }
        else if(belowEntity->getName() == "Koopa") {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioJumpOnKoopa>(entity->getID(), belowEntity->getID()));
        }
        else if(belowEntity->getName() == "Piranha") {
          if(entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
            EventQueue &EQ = EventQueue::getInstance();
            EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
          }
          else {
            EventQueue &EQ = EventQueue::getInstance();
            EQ.pushEvent(std::make_unique<MarioLargeToSmall>(entity->getID()));
          }
        }
        
      }
    }
    else if(below.lock()->getComponent<TextureComponent>().state == "Shell") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioJumpOnKoopa>(entity->getID(), below.lock()->getID()));
    }
    else if (below.lock()->hasComponent<PowerupTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioSmallToLarge>(entity->getID(), below.lock()->getID()));
    }
    else if(below.lock()->hasComponent<CoinTag>()) {
      below.lock()->destroy();
      entity->getComponent<MarioSoundComponent>().PlayCoinEffect();
      ScoreManager::getInstance().addScore(1);
    } 
    else if(below.lock()->getName() == "FlagPole") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<FinishLevelEvent>(entity->getID(),below.lock()->getID()));
    }
    else if (entity->getComponent<CharacterStateComponent>().getState() == "DROPPING") {
      entity->getComponent<CharacterStateComponent>().setEnumState("IDLE");
    }
    

  }

  // Above Collision
  if (cc.getAbove().lock() != nullptr) {
    auto aboveBlock = cc.getAbove().lock();
    if (aboveBlock->getName() == "BrokenBlock") {
      if (entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(
            new TriggerBrokenBlockWhenHitBySmall(
                aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBumpEffect();
      } else {
        aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(new TriggerBrokenBlockWhenHitByLarge(aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
      }
    }
    else if (aboveBlock->getName() == "QuestionBlock") {
      aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(new TriggerQuestionBlock(aboveBlock->getComponent<PositionComponent>().getPosition()));
      if(aboveBlock->getComponent<PowerUpComponent>().powerUp) {
        entity->getComponent<MarioSoundComponent>().PlayPowerupAppearsEffect();
      }
      else {
        entity->getComponent<MarioSoundComponent>().PlayCoinEffect();
      }
    }
    else if (aboveBlock->getName() == "Mushroom") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioSmallToLarge>(entity->getID(), aboveBlock->getID()));
    } 
    else if (aboveBlock->hasComponent<EnemyTag>()) {
      if(entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
      }
      else {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioLargeToSmall>(entity->getID()));
      }
    }
    else if(aboveBlock->hasComponent<CoinTag>()) {
      aboveBlock->destroy();
      entity->getComponent<MarioSoundComponent>().PlayCoinEffect();
      ScoreManager::getInstance().addScore(1);
    } 
    else if(aboveBlock->getName() == "FlagPole") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<FinishLevelEvent>(entity->getID(), aboveBlock->getID()));
    }
  }

  // Right Collision
  if (cc.getRight().lock() != nullptr) {
    auto rightBlock = cc.getRight().lock();
    if(rightBlock->hasComponent<EnemyTag>()) {
      if(rightBlock->getName() == "Koopa") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioTouchLeftKoopa>(entity->getID(), rightBlock->getID()));
      }
      else {
        if(entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
        }
        else {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioLargeToSmall>(entity->getID()));
        }
      }
    }
    else if(rightBlock->hasComponent<CoinTag>()) {
      rightBlock->destroy();
      entity->getComponent<MarioSoundComponent>().PlayCoinEffect();
      ScoreManager::getInstance().addScore(1);
    }
    else if(rightBlock->getName() == "Mushroom") {
      EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioSmallToLarge>(entity->getID(), rightBlock->getID()));
      }
    else if(rightBlock->getName() == "FlagPole") {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<FinishLevelEvent>(entity->getID(), rightBlock->getID()));
    }
  }

  // Left Collision
  if (cc.getLeft().lock() != nullptr) {
    auto leftBlock = cc.getLeft().lock();
    if (leftBlock->hasComponent<EnemyTag>()) {  
      if(leftBlock->getName() == "Koopa") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioTouchRightKoopa>(entity->getID(), leftBlock->getID()));
      }
      else {
        if(entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
        }
        else {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(std::make_unique<MarioLargeToSmall>(entity->getID()));
        }
      }
    }
    else if(leftBlock->hasComponent<CoinTag>()) {
      leftBlock->destroy();
      entity->getComponent<MarioSoundComponent>().PlayCoinEffect();
      ScoreManager::getInstance().addScore(1);
      // event: touch coin
    }
    else if(leftBlock->getName() == "Mushroom") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioSmallToLarge>(entity->getID(), leftBlock->getID()));
    }
    else if(leftBlock->getName() == "FlagPole") {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<FinishLevelEvent>(entity->getID(), leftBlock->getID()));
    }
  }
}
void CollisionHandlingSystem::handlePowerupCollision(Weak<AbstractEntity> _entity) {
    if (_entity.expired())
    throw std::runtime_error("Entity is expired");

  auto entity = _entity.lock();
  if(entity->getComponent<TextureComponent>().state == "Die") {
    entity->destroy();
    return;
  }
  CollisionComponent &collision = entity->getComponent<CollisionComponent>();
  auto above = collision.getAbove();
  auto below = collision.getBelow();
  auto left = collision.getLeft();
  auto right = collision.getRight();
  if(!above.expired() && above.lock()->hasComponent<PlayerTag>()) {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioSmallToLarge>(above.lock()->getID(), entity->getID()));
  }
  if(!below.expired() && below.lock()->hasComponent<PlayerTag>()) {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioSmallToLarge>(below.lock()->getID(), entity->getID()));
  } 
  if(!left.expired() && left.lock()->hasComponent<PlayerTag>()) {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioSmallToLarge>(left.lock()->getID(), entity->getID()));
  }  
  if(!right.expired() && right.lock()->hasComponent<PlayerTag>()) {
    EventQueue &EQ = EventQueue::getInstance();
    EQ.pushEvent(std::make_unique<MarioSmallToLarge>(right.lock()->getID(), entity->getID()));
  } 
}
void CollisionHandlingSystem::handleEnemyCollision(Weak<AbstractEntity> _entity) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");

  auto entity = _entity.lock();
  CollisionComponent &collision = entity->getComponent<CollisionComponent>();
  if(entity->getComponent<TextureComponent>().state == "Die") {
    entity->removeComponent<BoundingBoxComponent>();
    return;
  }
  auto above = collision.getAbove();
  auto below = collision.getBelow();
  auto left = collision.getLeft();
  auto right = collision.getRight();

  auto &trans = entity->getComponent<TransformComponent>();
  Vector2 v = trans.getVelocity();
  if (left.lock()) {
    auto leftEntity = left.lock();
    if (leftEntity->hasComponent<PlayerTag>()) {      
      if(leftEntity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioDieEvent>(leftEntity->getID()));
      }
      else {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioLargeToSmall>(leftEntity->getID()));
      }
    }
  }
  if (right.lock()) {
    auto rightEntity = right.lock();
    if (rightEntity->hasComponent<PlayerTag>()) {      
      if(rightEntity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioDieEvent>(rightEntity->getID()));
      }
      else {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioLargeToSmall>(rightEntity->getID()));
      }
    }
  }
  if (below.lock()) {
    auto belowEntity = below.lock();
    if (belowEntity->hasComponent<PlayerTag>()) {      
      if(belowEntity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioDieEvent>(belowEntity->getID()));
      }
      else {
        EventQueue &EQ = EventQueue::getInstance();
        EQ.pushEvent(std::make_unique<MarioLargeToSmall>(belowEntity->getID()));
      }
    }
  }
  trans.setVelocity(v);
}
void CollisionHandlingSystem::handleAICollision(Weak<AbstractEntity> _entity) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");

  auto entity = _entity.lock();

  CollisionComponent &collision = entity->getComponent<CollisionComponent>();
  auto above = collision.getAbove();
  auto below = collision.getBelow();
  auto left = collision.getLeft();
  auto right = collision.getRight();

  auto &trans = entity->getComponent<TransformComponent>();
  Vector2 v = trans.getVelocity();

  if (left.lock()) {
    if(left.lock()->getName() == "Koopa" && left.lock()->getComponent<TextureComponent>().state == "Shell-Moving") {
      entity->getComponent<TextureComponent>().changeState("Die");
      v.x = 0.f;
    }
    else {
      if(entity->getName() == "Koopa"){
        std::string state = entity->getComponent<TextureComponent>().state;
        if(state == "Shell-Moving") {
          if(left.lock()->hasComponent<EnemyTag>()){
            left.lock()->getComponent<TextureComponent>().changeState("Die");
            left.lock()->getComponent<TransformComponent>().setVelocity({0,0});
            v.x = ENEMY_SPEED * 3;
          }
          else {
            v.x = -(ENEMY_SPEED * 3);
            entity->getComponent<TextureComponent>().changeState("Shell-Moving");
          }
        }
        else v.x = -ENEMY_SPEED;
      }
      else v.x = -ENEMY_SPEED; 
      if(entity->getName() == "Koopa" && entity->hasComponent<EnemyTag>() == false && left.lock()->hasComponent<PlayerTag>()) {
        entity->addComponent<EnemyTag>();
      }
    }
  }
  if (right.lock()) {
    if(right.lock()->getName() == "Koopa" && right.lock()->getComponent<TextureComponent>().state == "Shell-Moving") {
      entity->getComponent<TextureComponent>().changeState("Die");
      v.x = 0.f;
    }
    else {
      if(entity->getName() == "Koopa"){
        std::string state = entity->getComponent<TextureComponent>().state;
        if(state == "Shell-Moving") {
          if(right.lock()->hasComponent<EnemyTag>()){
            right.lock()->getComponent<TextureComponent>().changeState("Die");
            right.lock()->getComponent<TransformComponent>().setVelocity({0,0});
            v.x = -(ENEMY_SPEED * 3);
          }
          else {
            v.x = (ENEMY_SPEED * 3);
            entity->getComponent<TextureComponent>().changeState("Shell-Moving");
          }
        }
        else v.x = ENEMY_SPEED;
      }
      else v.x = ENEMY_SPEED; 
      if(entity->getName() == "Koopa" && entity->hasComponent<EnemyTag>() == false && right.lock()->hasComponent<PlayerTag>()) {
        entity->addComponent<EnemyTag>();
      }
    }
    
  }
  if (below.lock() == nullptr)
    v.y = 50.0f;
  if(entity->getName() == "Koopa"){
    if(entity->getComponent<TextureComponent>().state == "Shell-Moving" || entity->getComponent<TextureComponent>().state == "Shell") {}
    else {
      if (v.x < 0.0f)
        entity->getComponent<TextureComponent>().changeState("Left-Moving");
      if (v.x > 0.0f)
        entity->getComponent<TextureComponent>().changeState("Right-Moving");
    }
  }
  else {
    if (v.x < 0.0f)
      entity->getComponent<TextureComponent>().changeState("Left-Moving");
    if (v.x > 0.0f)
      entity->getComponent<TextureComponent>().changeState("Right-Moving");
  }
  trans.setVelocity(v);
}
