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
	//AddValue(1000);
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

void MainCurrency::SubtractValue(int Value)
{
	cout << CurrentValue << '-' << Value << '=';
	CurrentValue -= Value;
	cout << CurrentValue << endl;
	CounterUpdate();
}

int MainCurrency::ReturnValue()
{
	return CurrentValue;
}

void MainCurrency::SetValue(int value)
{
	CurrentValue = value;
	CounterUpdate();
}