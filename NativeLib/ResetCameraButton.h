#pragma once
#include "CommonLib.h"
#include <TextureButton.hpp>
#include "CameraController.h"
#include <SceneTree.hpp>

class ResetCameraButton :
    public TextureButton
{
	GODOT_CLASS(ResetCameraButton, TextureButton);

public:
	static void _register_methods();
	void _init();

	void _on_ResetCameraButton_pressed();
	static ResetCameraButton* GetSingleton();
	void SetEnabled(bool state);

private:
	static inline ResetCameraButton* instance;
	bool enabled = false;
};

