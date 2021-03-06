#pragma once
#include <TextureButton.hpp>
#include <AnimationPlayer.hpp>
#include <Label.hpp>
#include <AudioStreamPlayer.hpp>

#include "CommonLib.h"
#include "SmartLabel.h"
#include "MainCurrency.h"
#include "DataLoader.h"

class UpgradeButton :
    public TextureButton
{
	GODOT_CLASS(UpgradeButton, TextureButton);

	float default_property = 1.0f;
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
	void SetUpgradeNumers(int num);

	int timesBought = 0;

private:
	AnimationPlayer* Animator;
	Label* SubstractAnim;

	AudioStreamPlayer* SubstractValute;
};

