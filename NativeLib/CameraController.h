#pragma once

#include "CommonLib.h"
#include <Camera2D.hpp>
#include "Oblast.h"
#include <Viewport.hpp>
#include "GameManager.h"
//#include <OS.hpp>

class Oblast;

class CameraController :
    public Camera2D
{
	GODOT_CLASS(CameraController, Camera2D);

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _physics_process(float delta);
	static CameraController* GetSingleton();
	void ZoomCameraToOblast(Oblast* oblast);
	void ZoomToDefault();
	bool IsMoving() { return moving; }

private:
	static inline CameraController* instance;
	Vector2 screenSize;
	float safeZone = 0.1;
	Vector2 newPosition;
	Vector2 newZoom;
	Vector2 defaultOffset;
	Vector2 defaultZoom;
	bool moving = false;

	
};

