#include "Components/BoundingBox.h"
#include "AbstractEntity.h"
#include "globals.h"
#include "Components/Collision.h"
#include "Components/Transform.h"
CollisionComponent::CollisionComponent()
    : Component("CollisionComponent"), entities(nullptr) {
        contact.resize(4);
        for(int i = 0; i < 4; i++) contact[i] = nullptr;
    }
CollisionComponent::CollisionComponent(Shared<std::vector<Shared<AbstractEntity>>> _entities)
    : Component("CollisionComponent"), entities(_entities) {
        contact.resize(4);
        for(int i = 0; i < 4; i++) contact[i] = nullptr;
    }

CollisionComponent::~CollisionComponent() {
    entities = nullptr;
}
void CollisionComponent::init() {}
bool RayVsRect(const Vector2& ray_origin, const Vector2& ray_dir, const Rectangle &target, Vector2& contact_point, 
    Vector2& contact_normal, float& t_hit_near)
{
    contact_normal = { 0,0 };
    contact_point = { 0,0 };

    // Cache division
    Vector2 invdir =(Vector2){1.0f / ray_dir.x, 1.0f/ray_dir.y};

    // Calculate intersections with rectangle bounding axes
    Vector2 t_near = (Vector2){(target.x - ray_origin.x) * invdir.x, (target.y - ray_origin.y) * invdir.y};
    Vector2 t_far = (Vector2){(target.x + target.width - ray_origin.x) * invdir.x, (target.y + target.height - ray_origin.y) * invdir.y};

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection		
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contact_point = ray_origin + (Vector2){t_hit_near * ray_dir.x, t_hit_near * ray_dir.y};

    if (t_near.x > t_near.y)
        if (invdir.x < 0)
            contact_normal = { 1, 0 };
        else
            contact_normal = { -1, 0 };
    else if (t_near.x < t_near.y)
        if (invdir.y < 0)
            contact_normal = { 0, 1 };
        else
            contact_normal = { 0, -1 };

    // Note if t_near == t_far, collision is principly in a diagonal
    // so pointless to resolve. By returning a CN={0,0} even though its
    // considered a hit, the resolver wont change anything.
    return true;
}
bool CollisionComponent::DynamicRectVsRect(const float deltaTime, const Rectangle &r_static,
    Vector2& contact_point, Vector2& contact_normal, float& contact_time)
{
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
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
    Vector2 ray_origin = (Vector2){position.x + size.x/2.0f, position.y + size.y/2.0f};
    Vector2 ray_dir = (Vector2){velocity.x * deltaTime, velocity.y * deltaTime};
    if (RayVsRect(ray_origin, ray_dir, expanded_target, contact_point, contact_normal, contact_time))
        return (contact_time >= 0.0f && contact_time < 1.0f);
    else
        return false;
}
bool CollisionComponent::ResolveDynamicRectVsRect(const float deltaTime, Shared<AbstractEntity> r_static)
{
    Vector2 contact_point, contact_normal;
    float contact_time = 0.0f;
    Vector2 position = r_static->getComponent<PositionComponent>().getPosition();
    Vector2 size = r_static->getComponent<BoundingBoxComponent>().getSize();
    Rectangle bbOtherEntity = (Rectangle){position.x, position.y, size.x, size.y};
    if (DynamicRectVsRect(deltaTime, bbOtherEntity, contact_point, contact_normal, contact_time))
    {
        if (contact_normal.y > 0.0f) contact[0] = r_static; 
        else contact[0] = nullptr;

        if (contact_normal.x < 0.0f) contact[1] = r_static;
        else contact[1] = nullptr;

        if (contact_normal.y < 0.0f) contact[2] = r_static;
        else contact[2] = nullptr;

        if (contact_normal.x > 0.0f) contact[3] = r_static;
        else contact[3] = nullptr;

        Vector2 velocity = entity->getComponent<TransformComponent>().getVelocity();
        velocity = velocity + (Vector2){contact_normal.x * std::fabs(velocity.x) * (1 - contact_time), contact_normal.y * std::fabs(velocity.y) * (1 - contact_time)};
        entity->getComponent<TransformComponent>().setVelocity(velocity);
        return true;
    }

    return false;
}
void CollisionComponent::update(float deltaTime) {
    std::vector<pair<int, float>> col;
    auto &otherEntity = *(entities);
    
	float t = 0, min_t = INFINITY;
    Vector2 cp, cn;
    for(int i = 0; i < (int)entities->size(); i++) {
        if(*otherEntity[i] == *entity) continue;
        Vector2 position = otherEntity[i]->getComponent<PositionComponent>().getPosition();
        Vector2 size = otherEntity[i]->getComponent<BoundingBoxComponent>().getSize();
        Rectangle bbOtherEntity = (Rectangle){position.x, position.y, size.x, size.y};
        if(DynamicRectVsRect(deltaTime, bbOtherEntity, cp, cn, t)) {
            col.push_back(std::make_pair(i, t));
        }
    }
    std::sort(col.begin(), col.end(), [&](const pair<int, float> &x, const pair<int, float> &y) {
        return x.second < y.second;
    });
    for(auto x : col)
        ResolveDynamicRectVsRect(deltaTime, otherEntity[x.first]);
    if(col.empty())
        for(int i = 0; i < 4; i++)
            contact[i] = nullptr;
}
Shared<AbstractEntity> CollisionComponent::getBelow() {
    return contact[2];
}
Shared<AbstractEntity> CollisionComponent::getAbove() {
    return contact[0];
}
Shared<AbstractEntity> CollisionComponent::getRight() {
    return contact[3];
}
Shared<AbstractEntity> CollisionComponent::getLeft() {
    return contact[1];
}
void CollisionComponent::setEntities(Shared<std::vector<Shared<AbstractEntity>>> _entities) {
    entities = _entities;
}