#pragma once
#include <Node2D.hpp>
#include <Label.hpp>
#include <Button.hpp>
#include <AnimationPlayer.hpp>

#include "CommonLib.h"
#include "Oblast.h"
#include "SmartLabel.h"
#include "MainCurrency.h"
#include "DataLoader.h"
#include "Oblast.h"

class Oblast;

class LevelPurchase :
	public Node2D
{
	GODOT_CLASS(LevelPurchase, Node2D);

public:
	static void _register_methods();
	void _init();
	void _ready();

	static LevelPurchase* GetSingleton();

	void _on_BuyButton_pressed();
	void _on_ReturnButton_pressed();

	void ShowLevelInfo(int LevelNumber, int LevelCost, int BotMoneyTransferSpeed, int BotTimeToProfit);

private:
	Label* NumberOfLevel;
	Label* SubstractAnim;

	AnimationPlayer* Animator;
	
	SmartLabel* MoneyTransferSpeed;
	SmartLabel* TimeToProfit;

	Button* BuyButton;
	Oblast* oblast;

	int MainCurrency;
	int LevelNumber;
	int LevelCost;

	static inline LevelPurchase* instance;
};