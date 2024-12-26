#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components/Collision.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "Interface.h"
#include "pch.h"

class System {
public:
  virtual ~System() = default;
};

class IDrawableSystem : virtual public System {
public:
  virtual ~IDrawableSystem() = default;
  virtual void draw(float dt) = 0;
};

class IUpdatableSystem : virtual public System {
public:
  virtual ~IUpdatableSystem() = default;
  virtual void update(float dt) = 0;
};

class TransformSystem : public IUpdatableSystem {
public:
  void update(float dt) override;
};

class AnimationSystem : public IDrawableSystem {
public:
  void draw(float dt) override;
};
class BlockSystem : public IUpdatableSystem {
public:
  void update(float dt) override;
};
class CollisionSystem : public IUpdatableSystem {
public:
  void update(float dt) override;

private:
  bool DynamicRectVsRect(const float deltaTime, const Rectangle &r_static,
                         Vector2 &contact_point, Vector2 &contact_normal,
                         float &contact_time, Weak<AbstractEntity> entity,
                         Vector2 secondVelo);
  bool ResolveDynamicRectVsRect(const float deltaTime,
                                Weak<AbstractEntity> r_static,
                                Weak<AbstractEntity> entity);

  void reset(CollisionComponent &cc);
};

bool RayVsRect(const Vector2 &ray_origin, const Vector2 &ray_dir,
               const Rectangle &target, Vector2 &contact_point,
               Vector2 &contact_normal, float &t_hit_near);

class CollisionHandlingSystem : public IUpdatableSystem {
public:
  void update(float dt) override;
  void handleAICollision(Weak<AbstractEntity> entity);
  void handlePlayerCollision(Weak<AbstractEntity> entity);
  void handleEnemyCollision(Weak<AbstractEntity> entity);

private:
  void handlePlayerEnemyCollision(Weak<AbstractEntity> player,
                                  Weak<AbstractEntity> enemy);
  void handlePlayerCoinCollision(Weak<AbstractEntity> player,
                                 Weak<AbstractEntity> coin);
};

class SwingSystem : public IUpdatableSystem {
public:
  void update(float dt) override;
};

class PlayerSystem : public IUpdatableSystem {
public:
  void update(float dt) override;

private:
  static void onUserClickButton(const Event &event);
};
#endif // SYSTEM_H
