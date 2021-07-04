#pragma once
#include <Label.hpp>

#include "CommonLib.h"

class LabelText :
	public Label
{
	GODOT_CLASS(LabelText, Label);

public:
	static void _register_methods();
	void _init();

	void SetValue(int Value);
	void SetValue(String Value);
	void SetValue(float Value);

	int ReturnValue();
};

