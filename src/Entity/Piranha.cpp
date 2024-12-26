#include "Components/Components_include.h"
#include "Entity/Enemy.h"

Weak<AbstractEntity> initPiranha(Vector2 position) {
  EntityManager &EM = EntityManager::getInstance();
  Shared<AbstractEntity> entity = EM.createEntity("Piranha").lock();
  Vector2 size = {14, 30};
  entity->addComponent<PositionComponent>(position);
  entity->addComponent<BoundingBoxComponent>(size);
  entity->addComponent<TextureComponent>();
  std::vector<Texture2D> textures;
  textures.push_back(TextureManager::getInstance().getTexture("Piranha1"));
  textures.push_back(TextureManager::getInstance().getTexture("Piranha2"));
  entity->getComponent<TextureComponent>().addTexture("Normal", textures, 0.1f,
                                                      true);
  entity->getComponent<TextureComponent>().changeState("Normal");
  entity->addComponent<EnemyTag>();
  entity->addComponent<SwingComponent>(position, 0);

  return entity;
}