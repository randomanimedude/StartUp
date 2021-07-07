#pragma once
#include "CommonLib.h"
#include <TextureButton.hpp>
#include "SmartLabel.h"
#include "MainCurrency.h"

class UpgradeButton :
    public TextureButton
{
	GODOT_CLASS(UpgradeButton, TextureButton);

	float property_multiplier = 1.1f;
	float default_price = 1.0f;
	float price_multiplier = 1.5f;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _process();
	void _on_UpgradeButton_pressed();
	void UpgradeLabels();
	void UpgradeProperty();


	int timesBought = 0;


};

