#pragma once

#include "CommonLib.h"
#include <Camera2D.hpp>
#include "Oblast.h"
#include <Viewport.hpp>

class Oblast;

class CameraController :
    public Camera2D
{
	GODOT_CLASS(CameraController, Camera2D);

public:
	static void _register_methods();
	void _init();

	void _ready();
	static CameraController* GetSingleton();
	void ZoomCameraToOblast(Oblast* oblast);

private:
	static inline CameraController* instance;
	Viewport* viewport;
	float safeZone = 0.1;
};

