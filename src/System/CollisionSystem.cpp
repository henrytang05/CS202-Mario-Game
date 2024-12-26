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
  for (auto tentity : Entities) {
    if (tentity.expired())
      throw std::runtime_error("Entity is expired");

    auto entity = tentity.lock();
    if (entity->hasComponent<PlayerTag>() &&
        entity->getComponent<CharacterStateComponent>().getState() == "DEATH") {
      continue;
    }
    std::vector<std::pair<int, float>> col;
    float t = 0, min_t = INFINITY;
    Vector2 cp, cn;
    for (int i = 0; i < (int)otherEntities.size(); i++) {
      if (*otherEntities[i].lock() == *entity)
        continue;

      if (otherEntities[i].lock()->hasComponent<PlayerTag>() &&
          otherEntities[i]
                  .lock()
                  ->getComponent<CharacterStateComponent>()
                  .getState() == "DEATH") {
        continue;
      }
      Vector2 position = otherEntities[i]
                             .lock()
                             ->getComponent<PositionComponent>()
                             .getPosition();
      Vector2 size = otherEntities[i]
                         .lock()
                         ->getComponent<BoundingBoxComponent>()
                         .getSize();
      Vector2 velo = {0.0f, 0.0f};
      if (otherEntities[i].lock()->hasComponent<TransformComponent>())
        velo = otherEntities[i]
                   .lock()
                   ->getComponent<TransformComponent>()
                   .getVelocity();
      Rectangle bbOtherEntity =
          (Rectangle){position.x, position.y, size.x, size.y};
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

    if (entity->hasComponent<AITag>()) {
      handleAICollision(entity);
    }
    if (entity->hasComponent<EnemyTag>()) {
      handleEnemyCollision(entity);
    }
    if (entity->hasComponent<PlayerTag>()) {
      handlePlayerCollision(entity);
    }
    entity->getComponent<CollisionComponent>().reset();
  }
}
void CollisionHandlingSystem::handlePlayerCollision(
    Weak<AbstractEntity> _entity) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");
  auto entity = _entity.lock();
  auto &cc = entity->getComponent<CollisionComponent>();
  auto &tf = entity->getComponent<TransformComponent>();
  // Below Collision
  if (cc.getBelow().lock() == nullptr) {
    if (entity->getComponent<CharacterStateComponent>().getState() == "DEATH") {
      tf.setVelocity({0.0f, tf.y + 10.0f});
      entity->getComponent<BoundingBoxComponent>().setSize({0.0f, 0.0f});
      if (entity->getComponent<PositionComponent>().getPosition().y >= 784.0f) {
        entity->removeComponent<PlayerTag>();
        sleep(1);
      }
      return;
    }
    entity->getComponent<CharacterStateComponent>().setEnumState("DROPPING");
    if (entity->getComponent<PositionComponent>().y > screenHeight * 1.2f) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
    }
  } else {
    if (cc.getBelow().lock()->hasComponent<EnemyTag>()) {
      auto below = entity->getComponent<CollisionComponent>().getBelow();
      if (!below.expired()) {
        auto belowEntity = below.lock();
        if (belowEntity->hasComponent<EnemyTag>()) {
          EventQueue &EQ = EventQueue::getInstance();
          EQ.pushEvent(
              std::make_unique<PlayerEnemyCollisionEvent>(entity, below));
        }
      }
    } else if (entity->getComponent<CharacterStateComponent>().getState() ==
               "DROPPING") {
      entity->getComponent<CharacterStateComponent>().setEnumState("IDLE");
    }
  }

  // Above Collision
  if (cc.getAbove().lock() != nullptr) {
    auto aboveBlock = cc.getAbove().lock();
    if (aboveBlock->getName() == "BrokenBlock") {
      if (entity->getComponent<CharacterStateComponent>().getSize() == "SMALL") {
        aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(new TriggerBrokenBlockWhenHitByLarge(aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBumpEffect();
      } else {
        // aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(new
        // TriggerBrokenBlockWhenHitByLarge(aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
      }
    } else if (aboveBlock->hasComponent<EnemyTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
    }
  }

  // Right Collision
  if (cc.getRight().lock() != nullptr) {
    auto rightBlock = cc.getRight().lock();
    if (rightBlock->hasComponent<EnemyTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
    }
  }

  // Left Collision
  if (cc.getLeft().lock() != nullptr) {
    auto leftBlock = cc.getLeft().lock();
    if (leftBlock->hasComponent<EnemyTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(entity->getID()));
    }
  }
}

void CollisionHandlingSystem::handleEnemyCollision(
    Weak<AbstractEntity> _entity) {
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
    auto leftEntity = left.lock();
    if (leftEntity->hasComponent<PlayerTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(leftEntity->getID()));
    }
  }
  if (right.lock()) {
    auto rightEntity = right.lock();
    if (rightEntity->hasComponent<PlayerTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(rightEntity->getID()));
    }
  }
  if (below.lock()) {
    auto belowEntity = below.lock();
    if (belowEntity->hasComponent<PlayerTag>()) {
      EventQueue &EQ = EventQueue::getInstance();
      EQ.pushEvent(std::make_unique<MarioDieEvent>(belowEntity->getID()));
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
  if (entity->getComponent<TextureComponent>().state == "Die") {
    // entity->destroy();
  }
  if (left.lock())
    v.x = -ENEMY_SPEED;
  if (right.lock())
    v.x = ENEMY_SPEED;
  if (below.lock() == nullptr)
    v.y = 10.0f;
  if (v.x < 0.0f)
    entity->getComponent<TextureComponent>().changeState("Left-Moving");
  if (v.x > 0.0f)
    entity->getComponent<TextureComponent>().changeState("Right-Moving");
  trans.setVelocity(v);
}
