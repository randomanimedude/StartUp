#include "UpgradeButton.h"

void UpgradeButton::_register_methods()
{
	register_method("_ready", &UpgradeButton::_ready);
	register_method("_process", &UpgradeButton::_process);
	register_method("_on_UpgradeButton_pressed", &UpgradeButton::_on_UpgradeButton_pressed);

	register_property("default_property", &UpgradeButton::default_property, 1.0f);
	register_property("property_multiplier", &UpgradeButton::property_multiplier, 1.1f);
	register_property("default_price", &UpgradeButton::default_price, 1.0f);
	register_property("price_multiplier", &UpgradeButton::price_multiplier, 1.5f);
}

void UpgradeButton::_init()
{
	connect("pressed", this, "_on_UpgradeButton_pressed");
}

void UpgradeButton::_ready()
{
	Animator = cast_to<AnimationPlayer>(get_node(NodePath((String)"/root/Node2D/Animator")));
	SubstractAnim = cast_to<Label>(get_node(NodePath((String)"/root/Node2D/SubstractAnim")));

	SubstractValute = cast_to<AudioStreamPlayer>(get_node(NodePath((String)"/root/Node2D/SubstractValute")));

	UpgradeLabels();
}

void UpgradeButton::_process()
{
	set_disabled(MainCurrency::GetSingleton()->ReturnValue() < default_price * (float)pow(price_multiplier, timesBought));
}

void UpgradeButton::_on_UpgradeButton_pressed()
{
	int value = (int)(default_price * (float)pow(price_multiplier, timesBought));

	MainCurrency::GetSingleton()->SubtractValue(value);

	SubstractValute->stop();
	SubstractValute->play();

	Animator->stop();
	SubstractAnim->set_text((String)"-" + String::num(value));
	Animator->play(String("SubstactValute"));

	++timesBought;
	UpgradeProperty();
	UpgradeLabels();
	DataLoader::GetSingleton()->set(get_parent()->get_name() + (String)"_bought", timesBought);
	DataLoader::GetSingleton()->SavePlayerUpgrades();
}

void UpgradeButton::UpgradeLabels()
{
	cast_to<SmartLabel>(get_node("SmartLabel"))->SetValue((int)(default_price * (float)pow(price_multiplier, timesBought)));
	cast_to<SmartLabel>(get_node("../SmartLabel"))->SetValue(default_property * (float)pow(property_multiplier, timesBought));
}

void UpgradeButton::UpgradeProperty()
{
	get_node("/root/Player")->set(get_parent()->get_name(), default_property * (float)pow(property_multiplier, timesBought));
}

void UpgradeButton::SetUpgradeNumers(int num)
{
	timesBought = num;
	UpgradeProperty();
	UpgradeLabels();
}

