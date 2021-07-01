#include "LookButton.h"
void LookButton::_register_methods()
{
	register_method("_on_Button_Pressed", &LookButton::_on_Button_Pressed);
	register_method("_ready", &LookButton::_ready);

	register_property("LevelNumber", &LookButton::LevelNumber, 1);
	register_property("LevelPrice", &LookButton::LevelPrice, 1);
}

void LookButton::_init()
{
	
}

void LookButton::_ready()
{
	connect("pressed", this, "_on_Button_Pressed");

	MainCurrency = MainCurrency::GetSingleton()->ReturnValue();

	if (MainCurrency > 0 && MainCurrency >= LevelPrice)
		set_disabled(false);

	else if (MainCurrency > 0 && MainCurrency < LevelPrice)
		set_disabled(true);

	if (DataLoader::GetSingleton()->ReturnLevelStatus(LevelNumber))
		set_visible(false);
}

void LookButton::_on_Button_Pressed()
{
	MainCurrency::GetSingleton()->SubtractValue(LevelPrice);
	DataLoader::GetSingleton()->OpenLevel(LevelNumber);
	set_visible(false);
}