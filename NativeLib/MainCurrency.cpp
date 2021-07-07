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

	DataLoader::GetSingleton()->UpdateMainCurrency(CurrentValue);
}

void MainCurrency::AddValue(int Value)
{
	CurrentValue += Value;

	CounterUpdate();
}

void MainCurrency::SubtractValue(int value)
{
	CurrentValue -= value;
	CounterUpdate();
}

void MainCurrency::SetValue(int value)
{
	CurrentValue = value;
	CounterUpdate();
}

int MainCurrency::ReturnValue()
{
	String StrValue = get_text();
	int value = StrValue.to_int();
	return value;
}
