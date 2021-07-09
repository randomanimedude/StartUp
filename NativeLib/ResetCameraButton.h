#pragma once
#include <TextureButton.hpp>
#include <SceneTree.hpp>

#include "CameraController.h"
#include "CommonLib.h"
#include "DataLoader.h"

class ResetCameraButton :
    public TextureButton
{
	GODOT_CLASS(ResetCameraButton, TextureButton);

public:
	static void _register_methods();
	void _init();
	void _ready();

	void _on_ResetCameraButton_pressed();

	static ResetCameraButton* GetSingleton();

	void SetEnabled(bool state);

private:
	static inline ResetCameraButton* instance;

	bool enabled = false;

	DataLoader* dataLoader;
};

