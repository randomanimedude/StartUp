#include "ResetButtons.h"

void ResetButtons::_register_methods()
{
	register_method("_on_ResetValuteButton_pressed", &ResetButtons::_on_ResetValuteButton_pressed);
	register_method("_on_ResetLevelProgres_pressed", &ResetButtons::_on_ResetLevelProgres_pressed);
	register_method("_on_ResetAllProgres_pressed", &ResetButtons::_on_ResetAllProgres_pressed);
	register_method("_on_AddValute_pressed", &ResetButtons::_on_AddValute_pressed);
}

void ResetButtons::_init()
{

}

void ResetButtons::_on_ResetValuteButton_pressed()
{
	DataLoader::GetSingleton()->UpdateMainCurrency(0);
	MainCurrency::GetSingleton()->SetValue(0);
}

void ResetButtons::_on_ResetLevelProgres_pressed()
{
	DataLoader::GetSingleton()->ResetLevelsProgres();

	for (int i = 0; i < 23; i++)
	{
		Oblast* oblast;
		oblast = cast_to<Oblast>(get_node(NodePath((String)"/root/Node2D/Map/" + String::num(i + 1))));
		oblast->Close();
	}
}

void ResetButtons::_on_ResetAllProgres_pressed()
{
	_on_ResetValuteButton_pressed();
	_on_ResetLevelProgres_pressed();
}

void ResetButtons::_on_AddValute_pressed()
{
	MainCurrency::GetSingleton()->AddValue(100);
}