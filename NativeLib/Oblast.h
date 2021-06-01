#pragma once

#include "CommonLib.h"
#include <Area2D.hpp>
#include <InputEventMouseButton.hpp>
#include <GlobalConstants.hpp>
#include <Sprite.hpp>
#include <MeshInstance2D.hpp>

class Oblast :
    public Area2D
{
	GODOT_CLASS(Oblast, Area2D);

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
	void changeColorTo(Color color, float force);

private:
	MeshInstance2D* mainSprite;
	Sprite* border;

	float colorChangeForce = 0;

	Color def = Color(255, 255, 255, 255)/255.0;
	Color blue = Color(97, 168, 239, 255)/255.0;
};

