#pragma once
#include <Camera2D.hpp>
#include <Viewport.hpp>

#include "CommonLib.h"
#include "Oblast.h"
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

	float safeZone = 0.1;

	Vector2 screenSize;
	Vector2 newPosition;
	Vector2 newZoom;
	Vector2 defaultOffset;
	Vector2 defaultZoom;

	bool moving = false;
};

