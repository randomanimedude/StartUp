#include "LevelPurchase.h"

void LevelPurchase::_register_methods()
{
	register_method("_ready", &LevelPurchase::_ready);
	register_method("_on_BuyButton_pressed", &LevelPurchase::_on_BuyButton_pressed);
	register_method("_on_ReturnButton_pressed", &LevelPurchase::_on_ReturnButton_pressed);
}

void LevelPurchase::_init()
{
	instance = this;
}

void LevelPurchase::_ready()
{
	NumberOfLevel = Node2D::cast_to<Label>(get_node("LevelNumber"));
	MoneyTransferSpeed = Node2D::cast_to<SmartLabel>(get_node("MoneyTransferSpeed"));
	TimeToProfit = Node2D::cast_to<SmartLabel>(get_node("TimeToProfit"));
	BuyButton = Node2D::cast_to<Button>(get_node("BuyButton"));
	
	SubstractAnim = cast_to<Label>(get_node(NodePath((String)"/root/Node2D/SubstractAnim")));
	Animator = cast_to<AnimationPlayer>(get_node(NodePath((String)"/root/Node2D/Animator")));

	SubstractAnim->set_self_modulate(Color(1, 1, 1, 0));
}

LevelPurchase* LevelPurchase::GetSingleton()
{
	return instance;
}

void LevelPurchase::ShowLevelInfo(int LevelNumber, int LevelCost, int BotMoneyTransferSpeed, int BotTimeToProfit)
{
	oblast = cast_to<Oblast>(get_node(NodePath((String)"/root/Node2D/Map/" + String::num(LevelNumber))));

	this->LevelNumber = LevelNumber;
	this->LevelCost = LevelCost;

	String levelNumber = String::num(LevelNumber) + (String)" level";
	NumberOfLevel->set_text(levelNumber);

	MoneyTransferSpeed->SetValue(BotMoneyTransferSpeed);
	TimeToProfit->SetValue(BotMoneyTransferSpeed);

	String cost = String::num(LevelCost);
	BuyButton->set_text(cost);

	MainCurrency = MainCurrency::GetSingleton()->ReturnValue();

	if (LevelCost > MainCurrency)
		BuyButton->set_disabled(true);

	else 
		BuyButton->set_disabled(false);

	set_visible(true);

	get_tree()->set_input_as_handled();
}

void LevelPurchase::_on_BuyButton_pressed()
{
	DataLoader::GetSingleton()->OpenLevel(LevelNumber);
	MainCurrency::GetSingleton()->SubtractValue(LevelCost);

	SubstractAnim->set_text((String)"-" + String::num(LevelCost));

	Animator->play(String("SubstactValute"));

	oblast->Open();
	set_visible(false);


}

void LevelPurchase::_on_ReturnButton_pressed()
{
	set_visible(false);
}