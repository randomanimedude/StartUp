#include "LabelText.h"

 void LabelText::_register_methods()
{
}

void LabelText::_init()
{

}

void LabelText::SetValue(int Value)
{
	String str = String::num(Value);
	set_text(str);
}

void LabelText::SetValue(String Value)
{
	set_text(Value);
}

int LabelText::ReturnValue()
{
	String str = get_text();

	int Value = str.to_int();

	return Value;
}