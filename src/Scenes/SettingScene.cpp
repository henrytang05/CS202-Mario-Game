#include "Scenes/SettingScene.h"
#include "Logger.h"
#include "Scenes/IntroScene.h"

SceneSpace::SettingScene::SettingScene() {
    SoundCtrl.PlayGroundTheme();
}

SceneSpace::SettingScene::~SettingScene()
{
    #ifdef _DEBUG
    Log("SettingScene destroyed");
    #endif
    delete QuitButton;
    delete musicSetting;
    delete soundSetting;
}

Shared<SceneSpace::Scene> SceneSpace::SettingScene::updateScene(float deltaTime)
{
    SoundCtrl.Update();
    Vector2 mousePos = GetMousePosition();
    bool isLeftClick = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    QuitButton->update(mousePos, isLeftClick);
    musicSetting->update(mousePos);
    soundSetting->update(mousePos);
    if (QuitButton->isPressed())
    {
        SoundCtrl.PlayTingSound();
        return std::make_shared<SceneSpace::IntroScene>();
    }
    MUSIC_VOLUME = musicSetting->getValue();
    SOUND_VOLUME = soundSetting->getValue();
    return nullptr;
}

void SceneSpace::SettingScene::draw()
{
    DrawTexture(background, 0, 0, WHITE);
    QuitButton->draw();
    musicSetting->draw();
    soundSetting->draw();
}

void SceneSpace::SettingScene::loadResources()
{
    background = LoadTexture("./assets/SettingBackground.png");
    QuitButton = new GUI::ImageButton(30, 20, "./assets/QuitButton.png",
                                       "./assets/Hover_QuitButton.png");
    musicSetting = new GUI::Slider(650, 220, 210, 30, 15, MUSIC_VOLUME, WHITE, GRAY);
    soundSetting = new GUI::Slider(650, 340, 210, 30, 15, SOUND_VOLUME, WHITE, GRAY);
}

void SceneSpace::SettingScene::init()
{
}

