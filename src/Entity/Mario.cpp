#include "Entity/Mario.h"
#include "Components/Components_include.h"
#include "EntityManager.h"

Weak<AbstractEntity> initMario() {
  EntityManager &EM = EntityManager::getInstance();
  Vector2 size({16, 20});
  Vector2 position = {0.0f, screenHeight - 100.0f};
  Vector2 velocity = {0, 10.0f};

  Shared<AbstractEntity> Mario = EM.createEntity("Mario").lock();
  Mario->addComponent<PlayerTag>();
  Mario->addComponent<CollisionComponent>();
  Mario->addComponent<PositionComponent>(position);
  Mario->addComponent<TransformComponent>(velocity);
  Mario->addComponent<BoundingBoxComponent>(size);
  Mario->addComponent<MarioSoundComponent>();
  Mario->addComponent<CharacterStateComponent>();
  Mario->addComponent<CharacterParametersComponent>(133.59375f, 200.390625f, 182.8125f, 365.625f, 33.75f, 562.0f, 4.453125f,
  93.75f, 153.75f, -240.0f, 270.0f, 421.875f, 1800.0f);
  /*    
    float WALKING_ACC = ;
    float RUNNING_ACC = ;
    float NORMAL_DEC = ;
    float SKIDDING_DEC = ;
    float MIN_SKIDDING = ;
    float GRAVITY_DEC = ;
    float MIN_WALKING_VELO = ;
    float MAX_WALKING_VELO = ;
    float MAX_RUNNING_VELO = ;
    float JUMPING_VELO = ;
    float MAX_FALL = ;
    float FALL_ACC_A = ;
    float FALL_ACC = ;
  */
  auto &texture = Mario->addComponent<TextureComponent>();

  // SMALL RIGHT
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

  Mario->getComponent<MarioSoundComponent>().LoadSounds();
  return Mario;
}
