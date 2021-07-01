#pragma once
#include <Button.hpp>

#include "CommonLib.h"
#include "MainCurrency.h"
#include "DataLoader.h"
#include "Oblast.h"
class LookButton :
	public Button
{
	GODOT_CLASS(LookButton, Button);

public:

	static void _register_methods();
	void _init();
	void _ready();
	void _on_Button_Pressed();

	int LevelNumber;
	int LevelPrice;

private:
	int MainCurrency;
	Oblast oblast;
};

