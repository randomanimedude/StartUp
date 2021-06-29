#include "ResetCameraButton.h"

void ResetCameraButton::_register_methods()
{
	register_method("_on_ResetCameraButton_pressed", &ResetCameraButton::_on_ResetCameraButton_pressed);
}

void ResetCameraButton::_init()
{
	connect("pressed", this, "_on_ResetCameraButton_pressed");
	instance = this;
}

void ResetCameraButton::_on_ResetCameraButton_pressed()
{
	if(enabled)
		GameManager::GetSingleton()->UnselectOblast();
}

ResetCameraButton* ResetCameraButton::GetSingleton()
{
	return instance;
}

void ResetCameraButton::SetEnabled(bool state )
{
	enabled = state;
	set_visible(enabled);
}
