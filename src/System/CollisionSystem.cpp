#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Tags.h"
#include "EntityManager.h"
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
      Rectangle bbOtherEntity = (Rectangle){
          position.x + velo.x * dt, position.y + velo.y * dt,
          size.x + std::abs(velo.x) * dt, size.y + std::abs(velo.y) * dt};
      if (DynamicRectVsRect(dt, bbOtherEntity, cp, cn, t, entity)) {
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
  Rectangle bbOtherEntity = (Rectangle){position.x + velo.x * deltaTime,
                                        position.y + velo.y * deltaTime,
                                        size.x + std::abs(velo.x) * deltaTime,
                                        size.y + std::abs(velo.y) * deltaTime};
  if (DynamicRectVsRect(deltaTime, bbOtherEntity, contact_point, contact_normal,
                        contact_time, entity)) {
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
bool CollisionSystem::DynamicRectVsRect(const float deltaTime,
                                        const Rectangle &r_static,
                                        Vector2 &contact_point,
                                        Vector2 &contact_normal,
                                        float &contact_time,
                                        Weak<AbstractEntity> _entity) {
  if (_entity.expired())
    throw std::runtime_error("Entity is expired");
  auto entity = _entity.lock();
  Vector2 velocity = entity->getComponent<TransformComponent>().getVelocity();
  Vector2 size = entity->getComponent<BoundingBoxComponent>().getSize();
  Vector2 position = entity->getComponent<PositionComponent>().getPosition();
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
void CollisionHandlingSystem::configure() {
  EventQueue &EQ = EventQueue::getInstance();
  EQ.registerHandler(EventType::MarioJumpOnGoomba, this->onMarioJumpOnGoomba);
}


void CollisionHandlingSystem::onMarioJumpOnGoomba(const Event &event) {
  ASSERT(event.type == EventType::MarioJumpOnGoomba);
  const auto &MJOG = std::get<MarioJumpOnGoombaEvent>(event.data);
  EntityManager &EM = EntityManager::getInstance();
  auto _mario = EM.getEntityPtr(MJOG.marioID);
  auto _goomba = EM.getEntityPtr(MJOG.goombaID);

  ASSERT(!_mario.expired());
  ASSERT(!_goomba.expired());

  auto mario = _mario.lock();
  auto goomba = _goomba.lock();
  goomba->getComponent<TextureComponent>().changeState("Die");
  goomba->getComponent<TransformComponent>().setVelocity({0.0f, 0.0f});
  mario->getComponent<CharacterStateComponent>().setEnumState("JUMPING");
  mario->getComponent<TransformComponent>().setVelocity({mario->getComponent<TransformComponent>().x, -180.0f});
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
    entity->getComponent<CharacterStateComponent>().setEnumState("DROPPING");
  } else {
    if (cc.getBelow().lock()->hasComponent<EnemyTag>()) {
      auto below = entity->getComponent<CollisionComponent>().getBelow();
      if (!below.expired()) {
        auto belowEntity = below.lock();
        if (belowEntity->hasComponent<EnemyTag>()) {
          EventQueue &EQ = EventQueue::getInstance();
          Event event(EventType::MarioJumpOnGoomba, MarioJumpOnGoombaEvent{entity->getID(), belowEntity->getID()});
          EQ.pushEvent(event);
        }
      }
    } 
    else if (entity->getComponent<CharacterStateComponent>().getState() == "DROPPING") {
      entity->getComponent<CharacterStateComponent>().setEnumState("IDLE");
    }
  }

  // Above Collision
  if (cc.getAbove().lock() != nullptr) {
    auto aboveBlock = cc.getAbove().lock();
    if (aboveBlock->getName() == "BrokenBlock") {
      if (entity->getComponent<CharacterStateComponent>().getSize() ==
          "SMALL") {
        aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(
            new TriggerBrokenBlockWhenHitBySmall(
                aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBumpEffect();
      } else {
        aboveBlock->getComponent<BlockTriggerComponent>().setTrigger(
            new TriggerBrokenBlockWhenHitByLarge(
                aboveBlock->getComponent<PositionComponent>().getPosition()));
        entity->getComponent<MarioSoundComponent>().PlayBreakBlockEffect();
      }
    } else if (aboveBlock->hasComponent<EnemyTag>()) {
      // EXPLAIN: DIE PLAYER
      entity->getComponent<MarioSoundComponent>().PlayMarioDieEffect();
    }
  }

  // Right Collision
  if (cc.getRight().lock() != nullptr) {
    auto rightBlock = cc.getRight().lock();
    if (rightBlock->hasComponent<EnemyTag>()) {
      // EXPLAIN: DIE PLAYER
      entity->getComponent<MarioSoundComponent>().PlayMarioDieEffect();
    }
  }

  // Left Collision
  if (cc.getLeft().lock() != nullptr) {
    auto leftBlock = cc.getLeft().lock();
    if (leftBlock->hasComponent<EnemyTag>()) {
      // EXPLAIN: DIE PLAYER
      entity->getComponent<MarioSoundComponent>().PlayMarioDieEffect();
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
  if (left.lock() && left.lock()->hasComponent<PlayerTag>()) {
    left.lock()->getComponent<CollisionComponent>().setRight(entity);
  }
  if (right.lock() && right.lock()->hasComponent<PlayerTag>()) {
    right.lock()->getComponent<CollisionComponent>().setRight(entity);
  }
  if (below.lock() && below.lock()->hasComponent<PlayerTag>()) {
    below.lock()->getComponent<CollisionComponent>().setRight(entity);
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
