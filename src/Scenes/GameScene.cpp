#include "Scenes/GameScene.h"

#include <memory>

#include "Components/Components_include.h"
#include "Components/Position.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
#include "pch.h"
#include "raylib.h"
#include "Scenes/GuideScene.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera({0, 0}) {}

void GameScene::init() {
  GuideButton = new GUI::ImageButton(30, 20, "./assets/GuideButton.png",
                                      "./assets/Hover_GuideButton.png");
  time = 360.f;
  entityFactory = std::make_unique<EntityFactory>();
  if(isMario) player = entityFactory->createMario();
  else player = entityFactory->createLuigi();
  entities.push_back(player);
  gameOver = false;
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  camera.target.y = 784.0f - 186.0f;
  camera.zoom = 2.0f;
  SoundCtrl.PlayGroundTheme();
  for (auto &entity : entities) {
    if (entity->hasComponent<CollisionComponent>()) {
      entity->getComponent<CollisionComponent>().setEntities(
          Shared<std::vector<Shared<AbstractEntity>>>(&entities));
    }
  }
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  // Loading BackGround
  Image bImage = LoadImage("Map/BackGroundnew.png");
  background = LoadTextureFromImage(bImage);
  UnloadImage(bImage);
  // Create Map
  entities = mapRenderer.createMap("Map/Level1new.json");
}
void GameScene::draw() {
  BeginMode2D(camera);
  DrawTexture(background, 0, 0, WHITE);
  for (auto &entity : entities) {
    if (entity != nullptr)
      entity->draw();
  }
  EndMode2D();
  DrawText(TextFormat("Time: %03i", (int)time), 1200, 35, GAMEPLAY_TEXT_SIZE,
           WHITE);
  GuideButton->draw();
}
Shared<Scene> GameScene::updateScene(float deltaTime) {
  this->update(deltaTime);

  Vector2 mousePos = GetMousePosition();
  bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  GuideButton->update(mousePos, isLeftClick);
  if(GuideButton->isPressed())
  {
    SoundCtrl.PlayTingSound();
    return std::make_unique<SceneSpace::GuideScene>();
  }

  if(player->checkAlive() == false) {
    SoundCtrl.Pause();
  }
  if(player->checkOver()) {
    return std::make_unique<IntroScene>();
  } 
  return nullptr;
}
void GameScene::update(float deltaTime) {
  time -= deltaTime;
  for (auto &entity : entities) {
    entity->update(deltaTime);
    // if (entity->hasAllComponents<PositionComponent, TransformComponent,
    //                              EnemyTag>())
    //   systems[0]->update(entity, deltaTime);

  }
  camera.target.x = player->getComponent<PositionComponent>().getPosition().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= screenWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth - screenWidth / (2.0f * camera.zoom);
  SoundCtrl.Update((int)time);
}

bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
