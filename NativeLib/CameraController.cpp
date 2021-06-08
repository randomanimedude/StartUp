#include "CameraController.h"

void CameraController::_register_methods()
{
	register_method("_ready", &CameraController::_ready);
	register_method("_physics_process", &CameraController::_physics_process);
}

void CameraController::_init()
{
	instance = this;
}

void CameraController::_ready()
{
	viewport = get_viewport();
	defaultOffset = get_offset();
	defaultZoom = get_zoom();
}

void CameraController::_physics_process(float delta)
{
	if (IsMoving())
	{
		float t = 0.2;
		set_offset(Vector2(lerp(get_offset().x, newOffset.x, t), lerp(get_offset().y, newOffset.y, t)));
		set_zoom(Vector2(lerp(get_zoom().x, newZoom.x, t), lerp(get_zoom().y, newZoom.y, t)));
		if ((get_offset().distance_squared_to(newOffset) + get_zoom().distance_squared_to(newZoom)) < 0.01)
		{
			set_offset(newOffset);
			set_zoom(newZoom);
			moving = false;
		}
	}
}

CameraController* CameraController::GetSingleton()
{
	return instance;
}

void CameraController::ZoomCameraToOblast(Oblast* oblast)
{
	float scale = max<float>(oblast->GetSize().height / viewport->get_size().height, oblast->GetSize().width / viewport->get_size().width) * (1 + safeZone);
	newZoom = Vector2(scale, scale);
	newOffset = oblast->get_global_position();

	moving = true;
}

void CameraController::ZoomToDefault()
{
	newZoom = defaultZoom;
	newOffset = defaultOffset;

	moving = true;
}


