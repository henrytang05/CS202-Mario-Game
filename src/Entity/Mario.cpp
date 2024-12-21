#include "Entity/Mario.h"
#include "Components/Components_include.h"

Mario::Mario()
    : PlayableEntity("Mario") {
  Vector2 size({16, 20});
  Vector2 position = {0.0f, screenHeight - 100.0f};
  Vector2 velocity = {0, 0};

  addComponent<CollisionComponent>();
  addComponent<PositionComponent>(position);
  addComponent<TransformComponent>(velocity);
  addComponent<BoundingBoxComponent>(size);
  addComponent<MarioSoundComponent>();
  auto &texture = addComponent<TextureComponent>();

  //SMALL RIGHT
  std::vector<Texture2D> textures;
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Idle.png"));
  texture.addTexture("SMALL-RIGHT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Moving.png"));
  texture.addTexture("SMALL-RIGHT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Skidding.png"));
  texture.addTexture("SMALL-RIGHT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Jumping.png"));
  texture.addTexture("SMALL-RIGHT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Dropping.png"));
  texture.addTexture("SMALL-RIGHT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Death.png"));
  texture.addTexture("SMALL-RIGHT-DEATH", textures);
  textures.clear();

  // SMALL LEFT
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Idle.png"));
  texture.addTexture("SMALL-LEFT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Moving.png"));
  texture.addTexture("SMALL-LEFT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Skidding.png"));
  texture.addTexture("SMALL-LEFT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Jumping.png"));
  texture.addTexture("SMALL-LEFT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Dropping.png"));
  texture.addTexture("SMALL-LEFT-DROPPING", textures);
  textures.clear();
  
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Death.png"));
  texture.addTexture("SMALL-LEFT-DEATH", textures);
  textures.clear();

  // LARGE RIGHT
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Idle.png"));
  texture.addTexture("LARGE-RIGHT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Moving.png"));
  texture.addTexture("LARGE-RIGHT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Skidding.png"));
  texture.addTexture("LARGE-RIGHT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Jumping.png"));
  texture.addTexture("LARGE-RIGHT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Dropping.png"));
  texture.addTexture("LARGE-RIGHT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Duckling.png"));
  texture.addTexture("LARGE-RIGHT-DUCKLING", textures);
  textures.clear();

  // LARGE LEFT
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Idle.png"));
  texture.addTexture("LARGE-LEFT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Moving.png"));
  texture.addTexture("LARGE-LEFT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Skidding.png"));
  texture.addTexture("LARGE-LEFT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Jumping.png"));
  texture.addTexture("LARGE-LEFT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Dropping.png"));
  texture.addTexture("LARGE-LEFT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Duckling.png"));
  texture.addTexture("LARGE-LEFT-DUCKLING", textures);
  textures.clear();
  texture.changeState("SMALL-RIGHT-IDLE");

  getComponent<MarioSoundComponent>().LoadSounds();
}
