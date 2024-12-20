#include "Entity/Mario.h"
#include "Components/Components_include.h"

Mario::Mario()
    : PlayableEntity("Mario") {
  Vector2 size({16, 20});
  Vector2 position = {0.0f, 0.0f};
  Vector2 velocity = {0, 0};

  addComponent<CollisionComponent>();
  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity);
  addComponent<BoundingBoxComponent>(size);
  addComponent<TextureComponent>();
  addComponent<MarioSoundComponent>();

  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-IDLE", "./assets/Mario/Small-Right-Idle.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-MOVING", "./assets/Mario/Small-Right-Moving.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-SKIDDING", "./assets/Mario/Small-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-JUMPING", "./assets/Mario/Small-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture("SMALL-RIGHT-DROPPING", "./assets/Mario/Small-Right-Dropping.png");

  getComponent<TextureComponent>().addTexture("SMALL-LEFT-IDLE", "./assets/Mario/Small-Left-Idle.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-MOVING", "./assets/Mario/Small-Left-Moving.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-SKIDDING", "./assets/Mario/Small-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-JUMPING", "./assets/Mario/Small-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture("SMALL-LEFT-DROPPING", "./assets/Mario/Small-Left-Dropping.png");
  
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-IDLE", "./assets/Mario/Large-Right-Idle.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-MOVING", "./assets/Mario/Large-Right-Moving.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-SKIDDING", "./assets/Mario/Large-Right-Skidding.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-JUMPING", "./assets/Mario/Large-Right-Jumping.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-DROPPING", "./assets/Mario/Large-Right-Dropping.png");
  getComponent<TextureComponent>().addTexture("LARGE-RIGHT-DUCKLING", "./assets/Mario/Large-Right-Duckling.png");

  getComponent<TextureComponent>().addTexture("LARGE-LEFT-IDLE", "./assets/Mario/Large-Left-Idle.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-MOVING", "./assets/Mario/Large-Left-Moving.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-SKIDDING", "./assets/Mario/Large-Left-Skidding.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-JUMPING", "./assets/Mario/Large-Left-Jumping.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-DROPPING", "./assets/Mario/Large-Left-Dropping.png");
  getComponent<TextureComponent>().addTexture("LARGE-LEFT-DUCKLING", "./assets/Mario/Large-Left-Duckling.png");

  getComponent<MarioSoundComponent>().LoadSounds();
}
