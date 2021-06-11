#include "ResetCameraButton.h"

void ResetCameraButton::_register_methods()
{
	register_method("_on_ResetCameraButton_pressed", &ResetCameraButton::_on_ResetCameraButton_pressed);
}

void ResetCameraButton::_init()
{
	connect("pressed", this, "_on_ResetCameraButton_pressed");
}

void ResetCameraButton::_on_ResetCameraButton_pressed()
{
	//CameraController::GetSingleton()->ZoomToDefault();
	GameManager::GetSingleton()->UnselectOblast();
}
