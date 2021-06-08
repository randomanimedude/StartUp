#include "CameraController.h"

void CameraController::_register_methods()
{
	register_method("_ready", &CameraController::_ready);
}

void CameraController::_init()
{
	instance = this;
}

void CameraController::_ready()
{
	viewport = get_viewport();
}

CameraController* CameraController::GetSingleton()
{
	return instance;
}

void CameraController::ZoomCameraToOblast(Oblast* oblast)
{
	set_offset(oblast->get_global_position());
	float scale = max<float>(oblast->GetSize().height / viewport->get_size().height, oblast->GetSize().width / viewport->get_size().width) * (1 + safeZone);
	set_zoom(Vector2(scale, scale));
}


