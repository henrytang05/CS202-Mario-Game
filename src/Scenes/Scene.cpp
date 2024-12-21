#include "Scenes/Scene.h"
namespace SceneSpace {
    Scene::Scene()
    {
        SoundCtrl.LoadSounds();
    }
    Scene::~Scene() = default;
}

void SceneSpace::Scene::setEnd(bool end)
{
    isEnd = end;
}

bool SceneSpace::Scene::checkEnd()
{
    return isEnd;
}
