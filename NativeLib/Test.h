#pragma once
#include "CommonLib.h"
#include <Area2D.hpp>
#include <GlobalConstants.hpp>
#include <InputEventMouseButton.hpp>


class Test :
    public Area2D
{
    GODOT_CLASS(Test, Area2D);

public:
	static void _register_methods();
	void _init();

	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
};

