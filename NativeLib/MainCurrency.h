#pragma once
#include <Label.hpp>

#include "CommonLib.h"
#include "DataLoader.h"

class MainCurrency :
	public Label
{
	GODOT_CLASS(MainCurrency, Label);

public:
	static void _register_methods();
	void _init();

	void AddValue(int Value);
	bool SubtractValue(int Value);

	int ReturnValue();

private:
	void CounterUpdate();

	int CurrentValue = 0;
};


