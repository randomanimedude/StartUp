#pragma once
#include "CommonLib.h"
#include "DataLoader.h"
#include "GameManager.h"
#include <Node2D.hpp>
#include <TextureButton.hpp>

class TutorialWindow :
    public Node2D
{
	GODOT_CLASS(TutorialWindow, Node2D);

	int tutorial_step = 1;

public:
	static void _register_methods();
	void _init();

	void _ready();

	void Close();

private:
	DataLoader* dataLoader;
};

