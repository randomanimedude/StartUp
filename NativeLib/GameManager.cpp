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

}

void GameManager::SelectOblast(Oblast* oblast)
{
    camera->ZoomCameraToOblast(oblast);
}

GameManager* GameManager::GetSingleton()
{
    return instance;
}
