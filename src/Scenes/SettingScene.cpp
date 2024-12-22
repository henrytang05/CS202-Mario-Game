#include "Scenes/SettingScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"

SceneSpace::SettingScene::SettingScene() {
}

SceneSpace::SettingScene::~SettingScene()
{
    #ifdef _DEBUG
    Log("SettingScene destroyed");
    #endif
    delete musicSetting;
    delete soundSetting;
    delete mario;
    delete luigi;
}

Unique<SceneSpace::Scene> SceneSpace::SettingScene::updateScene(float deltaTime)
{
    SoundCtrl.Update();
    Vector2 mousePos = GetMousePosition();
    bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    musicSetting->update(mousePos);
    soundSetting->update(mousePos);
    mario->update(mousePos, isLeftClick);
    if(mario->getChecked()){
        isMario = true;
        luigi->setChecked(false);
    }
    luigi->update(mousePos, isLeftClick);
    if(luigi->getChecked()){
        isMario = false;
        mario->setChecked(false);
    }
    MUSIC_VOLUME = musicSetting->getValue();
    SOUND_VOLUME = soundSetting->getValue();
    return nullptr;
}

void SceneSpace::SettingScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
    musicSetting->draw();
    soundSetting->draw();
    mario->draw();
    luigi->draw();
}

void SceneSpace::SettingScene::loadResources()
{
    background = LoadTexture("./assets/SettingBackground.png");
    musicSetting = new GUI::Slider(650, 220, 210, 30, 15, MUSIC_VOLUME, WHITE, GRAY);
    soundSetting = new GUI::Slider(650, 340, 210, 30, 15, SOUND_VOLUME, WHITE, GRAY);
    mario = new GUI::TickBox(680, 610, 25, isMario, WHITE, LIGHTGRAY, BLACK, BLACK, 3);
    luigi = new GUI::TickBox(840, 610, 25, !isMario, WHITE, LIGHTGRAY, BLACK, BLACK, 3);
}

void SceneSpace::SettingScene::init()
{
}

