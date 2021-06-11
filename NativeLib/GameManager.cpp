#include "GameManager.h"

void GameManager::_register_methods()
{
    register_method("_ready", &GameManager::_ready);
}

void GameManager::_init()
{
    instance = this;
}

void GameManager::_ready()
{
    camera = CameraController::GetSingleton();
    for (int i = 0; i < 24; ++i)
        oblasti[i] = cast_to<Oblast>(get_node(NodePath((String)"/root/Node2D/Map/" + String::num(i + 1))));
}

void GameManager::SelectOblast(Oblast* oblast)
{
    camera->ZoomCameraToOblast(oblast);
    selectedOblast = oblast;
    for (Oblast* region : oblasti)
    {
        if (region != selectedOblast)
            region->Hide();
    }
}

void GameManager::UnselectOblast()
{
    camera->ZoomToDefault();
    selectedOblast = nullptr;
    for (Oblast* oblast : oblasti)
        oblast->Show();
}

GameManager* GameManager::GetSingleton()
{
    return instance;
}
