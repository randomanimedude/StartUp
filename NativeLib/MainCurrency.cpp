#include "MainCurrency.h"

void MainCurrency::_register_methods()
{
	register_method("_ready", &MainCurrency::_ready);
}

void MainCurrency::_init()
{
	instance = this;
}

void MainCurrency::_ready() 
{
	CurrentValue = DataLoader::GetSingleton()->ReturnMainCurrency();
	AddValue(1000);
	CounterUpdate();
}

MainCurrency* MainCurrency::GetSingleton()
{
	return instance;
}

void MainCurrency::CounterUpdate()
{
	String str = String::num(CurrentValue);
	set_text(str);
}

void MainCurrency::AddValue(int Value)
{
	CurrentValue += Value;

	CounterUpdate();

	DataLoader::GetSingleton()->UpdateMainCurrency(CurrentValue);
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