#include "CameraController.h"

void CameraController::_register_methods()
{
	register_method("_ready", &CameraController::_ready);
	register_method("_process", &CameraController::_process);
}

void CameraController::_init()
{
	instance = this;
}

void CameraController::_ready()
{
	screenSize = get_viewport()->get_visible_rect().size;//OS::get_singleton()->get_window_size();//get_viewport();
	defaultOffset = get_offset();
	defaultZoom = get_zoom();
}

void CameraController::_process(float delta)
{
	if (IsMoving())
	{
		float local_t = transition_t * 60 * delta;	
		set_offset(Vector2(lerp(get_offset().x, newOffset.x, local_t), lerp(get_offset().y, newOffset.y, local_t)));
		set_zoom(Vector2(lerp(get_zoom().x, newZoom.x, local_t), lerp(get_zoom().y, newZoom.y, local_t)));
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
	float scale = max<float>((float)oblast->GetSize().height / screenSize.height, (float)oblast->GetSize().width / screenSize.width) * (1.0 + safeZone);
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


