#include "SmartLabel.h"

void SmartLabel::_register_methods(){}
void SmartLabel::_init(){}

void SmartLabel::SetValue(int Value)
{
	String str = String::num(Value);
	set_text(str);
}

void SmartLabel::SetValue(String Value)
{
	set_text(Value);
}

void SmartLabel::SetValue(float Value)
{
	String str = String::num(Value, 2);
	set_text(str);
}

int SmartLabel::ReturnValue()
{
	String str = get_text();

	int Value = str.to_int();

	return Value;
}