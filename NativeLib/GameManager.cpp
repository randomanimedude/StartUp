#include "GameManager.h"

void GameManager::_register_methods()
{
    register_method("_ready", &GameManager::_ready);
}

void GameManager::_init()
{
    instance = this;
    srand(time(0));
}

void GameManager::_ready()
{
    dataLoader = DataLoader::GetSingleton();

    MainMusic = cast_to<AnimationPlayer>(get_node(NodePath((String)"/root/Node2D/ChangeOfMusic")));

    flyingMoney = ResourceLoader::get_singleton()->load("res://Prefabs/FlyingMoney.tscn");

    camera = CameraController::GetSingleton();
    for (int i = 0; i < 24; ++i)
        oblasti[i] = cast_to<Oblast>(get_node(NodePath((String)"/root/Node2D/Map/" + String::num(i + 1))));
}

void GameManager::SelectOblast(Oblast* oblast)
{
    if (selectedOblast == nullptr && !camera->IsMoving())
    {
        selectedOblast = oblast;
        camera->ZoomCameraToOblast(selectedOblast);
        selectedOblast->ShowPieces();
        for (Oblast* region : oblasti)
        {
            if (region != selectedOblast)
                region->Hide();
        }

        MainMusic->play("TransitionToTheLevel");

        dataLoader->SetWindowsStatus(true);
        dataLoader->SetIsLevelPlaying(true);
        dataLoader->SetWindowsStatusOnLevels(false);
    }
}

void GameManager::UnselectOblast()
{
    if (selectedOblast != nullptr && !camera->IsMoving())
    {
        camera->ZoomToDefault();
        for (Oblast* oblast : oblasti)
            if (oblast != selectedOblast)
                oblast->Show();

        selectedOblast->HidePieces();
        selectedOblast->UnselectPiece();
        selectedOblast = nullptr;
        ResetCameraButton::GetSingleton()->SetEnabled(false);
        SetGameIsPlaying(false);

        MainMusic->play("TransitionToTheMenu");

        dataLoader->SetWindowsStatus(false);
        dataLoader->SetIsLevelPlaying(false);
        dataLoader->SetWindowsStatusOnLevels(true);
    }
}

void GameManager::SetGameIsPlaying(bool playing)
{
    gameIsPlaying = playing;
}

void GameManager::CheckIfOblastIsCompleted()
{
    if (selectedOblast != nullptr && selectedOblast->IsCompleted())
    {
        UnselectOblast();
    }
}

GameManager* GameManager::GetSingleton()
{
    return instance;
}
