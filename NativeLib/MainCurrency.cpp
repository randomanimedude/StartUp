#include "MainCurrency.h"

void MainCurrency::_register_methods()
{

}

void MainCurrency::_init()
{
	CurrentValue = DataLoader::GetSingleton()-> ReturnMainCurrency();
	CounterUpdate();
}

void MainCurrency::CounterUpdate()
{
	String str = String::num(CurrentValue);
	set_text(str);
}

void MainCurrency::AddValue(int Value)
{
	CurrentValue += Value;

	DataLoader::GetSingleton()->UpdateMainCurrency(CurrentValue);

	CounterUpdate();
}

bool MainCurrency::SubtractValue(int Value)
{
	if (CurrentValue - Value < 0)
		return false;

	CurrentValue -= Value;

	CounterUpdate();

	DataLoader::GetSingleton()->UpdateMainCurrency(CurrentValue);

	return true;
}

int MainCurrency::ReturnValue()
{
	return CurrentValue;
}