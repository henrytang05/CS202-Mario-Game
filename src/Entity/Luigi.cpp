#include "Entity/Luigi.h"
#include "Components/Components_include.h"

Luigi::Luigi() : PlayableEntity("Luigi"){
  Vector2 size({16, 20});
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0, 0};

  addComponent<CollisionComponent>();
  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  addComponent<MarioSoundComponent>();

  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-IDLE", "./assets/Luigi/Small-Right-Idle.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-MOVING", "./assets/Luigi/Small-Right-Moving.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-SKIDDING", "./assets/Luigi/Small-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-JUMPING", "./assets/Luigi/Small-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-DROPPING", "./assets/Luigi/Small-Right-Dropping.png");

  getComponent<TextureComponent>().addTexture("SMALL-LEFT-IDLE", "./assets/Luigi/Small-Left-Idle.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-MOVING", "./assets/Luigi/Small-Left-Moving.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-SKIDDING", "./assets/Luigi/Small-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-JUMPING", "./assets/Luigi/Small-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-DROPPING", "./assets/Luigi/Small-Left-Dropping.png");
  
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-IDLE", "./assets/Luigi/Large-Right-Idle.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-MOVING", "./assets/Luigi/Large-Right-Moving.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-SKIDDING", "./assets/Luigi/Large-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-JUMPING", "./assets/Luigi/Large-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-DROPPING", "./assets/Luigi/Large-Right-Dropping.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-DUCKLING", "./assets/Luigi/Large-Right-Duckling.png");

  getComponent<TextureComponent>().addTexture("LARGE-LEFT-IDLE", "./assets/Luigi/Large-Left-Idle.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-MOVING", "./assets/Luigi/Large-Left-Moving.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-SKIDDING", "./assets/Luigi/Large-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-JUMPING", "./assets/Luigi/Large-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-DROPPING", "./assets/Luigi/Large-Left-Dropping.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-DUCKLING", "./assets/Luigi/Large-Left-Duckling.png");
  
  getComponent<MarioSoundComponent>().LoadSounds();
}