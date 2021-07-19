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
	void _ready();

	static MainCurrency* GetSingleton();

	void AddValue(int Value);
	void SubtractValue(int Value);
	void CounterUpdate();
	void SetValue(int value);

	int ReturnValue();

private:
	int CurrentValue = 0;
	static inline MainCurrency* instance;
};


