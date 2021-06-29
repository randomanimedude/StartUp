#include "Bot.h"

void Bot::_register_methods()
{
	register_method("_physics_process", &Bot::_physics_process);

	register_property("color_r", &Bot::color_r, 255);
	register_property("color_g", &Bot::color_g, 255);
	register_property("color_b", &Bot::color_b, 255);
	register_property("update_t", &Bot::update_t, 2.0f);
	register_property("time_to_make_money", &Bot::time_to_make_money, 1.0f);
}

void Bot::_init()
{
	color = Color(color_r, color_g, color_b) / 255.0;
}

void Bot::_ready()
{
	oblast = cast_to<Oblast>(get_node(".."));
}

void Bot::_physics_process(float delta)
{
	timePassed += delta;
	if (timePassed > update_t)
	{
		DoStuff();
		timePassed -= delta;
	}
}

void Bot::DoStuff()
{
	//if (BestPiece()->GetPriceToConquer() < TotalMoney())
	//	for (Piece* piece : oblast->GetPieces())
	//		if (piece->owner == PieceOwner::BotAsOwner && piece->botOwner == this)
	//			BestPiece()->Conquer(piece->GetMoney(), piece);
}

void Bot::EarnMoneyAtPiece(Piece* piece, float& timePassed)
{
	int earnings = round(timePassed / time_to_make_money);
	piece->AddMoney(earnings);
	timePassed -= time_to_make_money * earnings;
}

Piece* Bot::BestPiece()
{
	Piece* bestPiece = nullptr;
	int price = 999999;
	for (Piece* piece : oblast->GetPieces())
	{
		if ((piece->owner != PieceOwner::BotAsOwner || piece->botOwner != this)&&piece->GetPriceToConquer()<price)
		{
			price = piece->GetPriceToConquer();
			bestPiece = piece;
		}
	}
	return bestPiece;
}

int Bot::TotalMoney()
{
	int money = 0;
	for (Piece* piece : oblast->GetPieces())
		if (piece->owner == PieceOwner::BotAsOwner && piece->botOwner == this)
			money += piece->GetMoney();
	return money;
}

//vector<Piece*> Bot::MyPieces()
//{
//	vector<Piece*> pieces;
//	for (Piece* piece : oblast->GetPieces())
//		if (piece->owner == PieceOwner::BotAsOwner && piece->botOwner == this)
//			pieces.push_back(piece);
//	return pieces;
//}
