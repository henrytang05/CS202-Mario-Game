#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components/Collision.h"
#include "EntityManager.h"
#include "Interface.h"

class System {
public:
  virtual ~System() = default;
};

class IDrawableSystem : public System {
public:
  virtual ~IDrawableSystem() = default;
  virtual void draw(EntityManager &EM, float dt) = 0;
};

class IUpdatableSystem : public System {
public:
  virtual ~IUpdatableSystem() = default;
  virtual void update(EntityManager &EM, float dt) = 0;
};

class TransformSystem : public IUpdatableSystem {
public:
  void update(EntityManager &EM, float dt) override;
};

class AnimationSystem : public IDrawableSystem {
public:
  void draw(EntityManager &EM, float dt) override;
};

class CollisionSystem : public IUpdatableSystem {
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
