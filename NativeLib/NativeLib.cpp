#include "CommonLib.h"
#include "Oblast.h"
#include "GameManager.h"
#include "CameraController.h"
#include "ResetCameraButton.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<Oblast>();
	register_class<GameManager>();
	register_class<CameraController>();
	register_class<ResetCameraButton>();
}