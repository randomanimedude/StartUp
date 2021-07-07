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

/// <summary>
/// The function updates the counter
/// </summary>
void MainCurrency::CounterUpdate()
{
	String str = String::num(CurrentValue);
	set_text(str);

	DataLoader::GetSingleton()->UpdateMainCurrency(CurrentValue);
}

/// <summary>
/// The function adds a certain value to the total amount of currency
/// </summary>
void MainCurrency::AddValue(int Value)
{
	CurrentValue += Value;

	CounterUpdate();
}

/// <summary>
/// The function subtracts a certain value from the total amount of currency
/// </summary>
void MainCurrency::SubtractValue(int value)
{
	CurrentValue -= value;
	CounterUpdate();
}

/// <summary>
/// The function sets the value of the common currency
/// </summary>
void MainCurrency::SetValue(int value)
{
	CurrentValue = value;
	CounterUpdate();
}

/// <summary>
/// the function returns the current value on the counter
/// </summary>
int MainCurrency::ReturnValue()
{
	String StrValue = get_text();
	int value = StrValue.to_int();
	return value;
}
