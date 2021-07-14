#pragma once
#include <TextureButton.hpp>
#include <Node2D.hpp>
#include <SceneTree.hpp>
#include <AudioStreamPlayer.hpp>

#include "CommonLib.h"
#include "GameManager.h"

class ProfileButton :
    public TextureButton
{
	GODOT_CLASS(ProfileButton, TextureButton);

	String window_name = "UpgradeMenu";

public:
	static void _register_methods();
	void _init();
	void _ready();

	void _on_ProfileButton_pressed();

private:
	Node2D* window;

	AudioStreamPlayer* ButtonsSound;

	DataLoader* dataLoader;
};

