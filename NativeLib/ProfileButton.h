#pragma once
#include "CommonLib.h"
#include "GameManager.h"
#include <TextureButton.hpp>
#include <Node2D.hpp>
#include <SceneTree.hpp>

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

	DataLoader* dataLoader;
};

