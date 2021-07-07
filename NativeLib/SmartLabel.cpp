#include "SmartLabel.h"

void SmartLabel::_register_methods(){}
void SmartLabel::_init(){}

/// <summary>
/// the function uses the int value to set the label text
/// </summary>
void SmartLabel::SetValue(int Value)
{
	String str = String::num(Value);
	set_text(str);
}

/// <summary>
/// the function uses the float value to set the label text
/// </summary>
void SmartLabel::SetValue(String Value)
{
	set_text(Value);
}

/// <summary>
///the function uses the string value to set the label text
/// </summary>
void SmartLabel::SetValue(float Value)
{
	String str = String::num(Value, 2);
	set_text(str);
}

/// <summary>
/// the function returns the value of the smart label
/// </summary>
int SmartLabel::ReturnValue()
{
	String str = get_text();

	int Value = str.to_int();

	return Value;
}