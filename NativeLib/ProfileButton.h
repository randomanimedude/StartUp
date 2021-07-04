#pragma once
#include "CommonLib.h"
#include <TextureButton.hpp>
#include <Node2D.hpp>

class ProfileButton :
    public TextureButton
{
	GODOT_CLASS(ProfileButton, TextureButton);

public:
	static void _register_methods();
	void _init();

	void _on_ProfileButton_pressed();
};

