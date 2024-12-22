#ifndef SYSTEM_H
#define SYSTEM_H

#include "AbstractEntity.h"
#include "Components/Collision.h"
#include "EntityManager.h"
class System {

public:
  virtual ~System() = default;
  virtual void update(EntityManager &EM, float dt) = 0;
};

class TransformSystem : public System {
public:
  void update(EntityManager &EM, float dt) override;
};

class AnimationSystem : public System {
public:
  void update(EntityManager &EM, float dt) override;
};

class CollisionSystem : public System {
public:
  void update(EntityManager &EM, float dt) override;

private:
  bool DynamicRectVsRect(const float deltaTime, const Rectangle &r_static,
                         Vector2 &contact_point, Vector2 &contact_normal,
                         float &contact_time, EntityManager &EM,
                         AbstractEntity &entity);
  bool ResolveDynamicRectVsRect(const float deltaTime, AbstractEntity &r_static,
                                EntityManager &EM, AbstractEntity &entity);

  void reset(CollisionComponent &cc);
};
bool RayVsRect(const Vector2 &ray_origin, const Vector2 &ray_dir,
               const Rectangle &target, Vector2 &contact_point,
               Vector2 &contact_normal, float &t_hit_near);

#endif // SYSTEM_H
