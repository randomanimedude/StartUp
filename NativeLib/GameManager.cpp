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
    selectedOblast = oblast;
    camera->ZoomCameraToOblast(selectedOblast);
    selectedOblast->ShowPieces();
    for (Oblast* region : oblasti)
    {
        if (region != selectedOblast)
            region->Hide();
    }
}

void GameManager::UnselectOblast()
{
    camera->ZoomToDefault();
    for (Oblast* oblast : oblasti)
        if(oblast!=selectedOblast)
            oblast->Show();
    selectedOblast->HidePieces();
    selectedOblast = nullptr;
}

GameManager* GameManager::GetSingleton()
{
    return instance;
}
