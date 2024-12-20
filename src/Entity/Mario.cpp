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
  addComponent<MarioSoundComponent>();
  auto &texture = addComponent<TextureComponent2>(0.1f, true, "SMALL-RIGHT-IDLE");

  //SMALL RIGHT
  std::vector<Texture2D> textures;
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Idle.png"));
  texture.addTextures("SMALL-RIGHT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Moving.png"));
  texture.addTextures("SMALL-RIGHT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Skidding.png"));
  texture.addTextures("SMALL-RIGHT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Jumping.png"));
  texture.addTextures("SMALL-RIGHT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Dropping.png"));
  texture.addTextures("SMALL-RIGHT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Right-Death.png"));
  texture.addTextures("SMALL-RIGHT-DEATH", textures);
  textures.clear();

  // SMALL LEFT
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Idle.png"));
  texture.addTextures("SMALL-LEFT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Moving.png"));
  texture.addTextures("SMALL-LEFT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Skidding.png"));
  texture.addTextures("SMALL-LEFT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Jumping.png"));
  texture.addTextures("SMALL-LEFT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Dropping.png"));
  texture.addTextures("SMALL-LEFT-DROPPING", textures);
  textures.clear();
  
  textures.push_back(LoadTexture("./assets/Mario/Small-Left-Death.png"));
  texture.addTextures("SMALL-LEFT-DEATH", textures);
  textures.clear();

  // LARGE RIGHT
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Idle.png"));
  texture.addTextures("LARGE-RIGHT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Moving.png"));
  texture.addTextures("LARGE-RIGHT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Skidding.png"));
  texture.addTextures("LARGE-RIGHT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Jumping.png"));
  texture.addTextures("LARGE-RIGHT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Dropping.png"));
  texture.addTextures("LARGE-RIGHT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Right-Duckling.png"));
  texture.addTextures("LARGE-RIGHT-DUCKLING", textures);
  textures.clear();

  // LARGE LEFT
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Idle.png"));
  texture.addTextures("LARGE-LEFT-IDLE", textures);
  textures.clear();

  
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Idle.png"));
  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Moving.png"));
  texture.addTextures("LARGE-LEFT-MOVING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Skidding.png"));
  texture.addTextures("LARGE-LEFT-SKIDDING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Jumping.png"));
  texture.addTextures("LARGE-LEFT-JUMPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Dropping.png"));
  texture.addTextures("LARGE-LEFT-DROPPING", textures);
  textures.clear();

  textures.push_back(LoadTexture("./assets/Mario/Large-Left-Duckling.png"));
  texture.addTextures("LARGE-LEFT-DUCKLING", textures);
  textures.clear();

  getComponent<MarioSoundComponent>().LoadSounds();
}
