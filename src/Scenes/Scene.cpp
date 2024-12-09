#include "Scenes/Scene.h"
namespace SceneSpace {
    Scene::Scene()
    {
        SoundCtrl.LoadSounds();
    }
    Scene::~Scene() = default;
}
