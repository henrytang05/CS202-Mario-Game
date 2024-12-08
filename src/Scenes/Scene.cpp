#include "Scenes/Scene.h"
#include "InputHandler.h"
namespace SceneSpace {
    Scene::Scene()
    {
        SoundCtrl.LoadSounds();
    }
    Scene::~Scene() = default;
}
