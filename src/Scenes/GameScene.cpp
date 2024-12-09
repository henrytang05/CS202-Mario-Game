#include "Scenes/GameScene.h"

#include <memory>

#include "Components/Camera.h"
#include "Components/Texture.h"
#include "Entity/EntityFactory.h"
#include "Entity/PlayableEntity.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"
#include "globals.h"
class TextureComponent;
namespace SceneSpace {

GameScene::GameScene() : Scene(), camera(addComponent<CameraComponent>()) {
  init();
}

void GameScene::init() {
  entityFactory = std::make_unique<EntityFactory>();
  Shared<Mario> mario = entityFactory->createMario();
  player = mario;
  entities.push_back(mario);
  camera.setTarget(*mario);

  // entities.push_back(luigi);
  // entities.push_back(goomba);
}

GameScene::~GameScene() {
#ifdef _DEBUG
  Log("GameScene destroyed");
#endif
}
void GameScene::loadResources() {
  tileFactory = TileFactory("Map/OverWorld.json", "Map/OverWorld.png");
  mapRenderer = MapRenderer("Map/Level1.json", tileFactory);
}
void GameScene::start() {
  gameOver = false;
  player = make_shared<Character>("./assets/Luigi-Small", 11,
                                  Vector2{0.0f, 0.0f}, Vector2{16, 23});
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.target.x = player->getPosition().x;
  camera.target.y = 784.0f - 186.0f;
  camera.zoom = 2.0f;
}
void GameScene::draw() {
  BeginMode2D(camera);
  mapRenderer.Render();
  player->draw();
  EndMode2D();
}
Shared<Scene> GameScene::update() {
  player->update();
  camera.target.x = player->getPosition().x;
  if (camera.target.x <= screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth / (2.0f * camera.zoom);
  if (camera.target.x >= screenWidth - screenWidth / (2.0f * camera.zoom))
    camera.target.x = screenWidth - screenWidth / (2.0f * camera.zoom);
  void GameScene::draw() {
    BeginMode2D(camera);
    DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
    // for (auto &entity : entities) {
    //   entity->draw();
    // }
    camera.setTarget(*player);
    player->draw();

    DrawLine(0.0f, ground, screenWidth, ground, BLACK);
    ClearBackground(RAYWHITE);
    EndMode2D();
    // for (Shared<Character> ch : characters) {
    //   ch->draw();
    // }
  }
  void GameScene::update() {
    for (auto &entity : entities) {
      entity->update();
    }
  }

  bool GameScene::isFinished() { return gameOver; }
} // namespace SceneSpace
