#pragma once
#include "CommonLib.h"
#include <Sprite.hpp>
#include <Area2D.hpp>
#include <Input.hpp>

class Test :
    public Sprite
{
    GODOT_CLASS(Test, Sprite);

public:
	static void _register_methods();
	void _init();

	void _ready();
};

