#pragma once
#include <Label.hpp>

#include "CommonLib.h"

class SmartLabel :
	public Label
{
	GODOT_CLASS(SmartLabel, Label);

public:
	static void _register_methods();
	void _init();

	void SetValue(int Value);
	void SetValue(float Value);
	void SetValue(String Value);

	int ReturnValue();
};

