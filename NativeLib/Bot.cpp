#include "Bot.h"

void Bot::_register_methods()
{
	register_method("_physics_process", &Bot::_physics_process);
	register_method("_ready", &Bot::_ready);

	register_property("color_r", &Bot::color_r, 255);
	register_property("color_g", &Bot::color_g, 255);
	register_property("color_b", &Bot::color_b, 255);
	register_property("update_t", &Bot::update_t, 2.0f);
	register_property("time_to_make_money", &Bot::time_to_make_money, 1.0f);
	register_property("money_speed", &Bot::money_speed, 1.0f);
}

void Bot::_init()
{
}

void Bot::_ready()
{
	color = Color(color_r, color_g, color_b, 255) / 255.0;
	oblast = cast_to<Oblast>(get_node("../.."));
}

void Bot::_physics_process(float delta)
{
	timePassed += delta;
	if (timePassed > update_t)
	{
		DoStuff();
		timePassed -= update_t;
	}
}

void Bot::DoStuff()
{
	vector<Piece*> myPieces = MyPieces();
	vector<Piece*> closestPieces;
	Piece * closest = ClosestPieceByLableTransform(BestPieces());
	switch (rand() % 5)
	{
	case 0:
		//all-in atack to closest among best piece by number 
		closestPieces = ClosestPiecesByNumber(BestPieces());
		if (closestPieces.size() > 0)
		{
			Piece* ataka = closestPieces[rand() % closestPieces.size()];
			if (ataka->GetPriceToConquer(this) < TotalMoney())
				for (Piece* piece : MyPieces())
					piece->TransferMoneyTo(ataka);
		}
		break;
	case 1:
		//all-in atack to closest among best piece by position
		if (closest != nullptr)
		{
			if (closest->GetPriceToConquer(this) < TotalMoney())
				for (Piece* piece : MyPieces())
					piece->TransferMoneyTo(closest);
		}
		break;
	case 2: case 3:
		//atack closest among best with one random piece
		if (closest != nullptr)
		{

			for (int i = 0; i < myPieces.size(); )
				if (closest->GetPriceToConquer(this) > myPieces[i]->GetMoney())
					myPieces.erase(myPieces.begin() + i);
				else
					++i;
			if (myPieces.size() > 0)
				myPieces[rand() % myPieces.size()]->TransferMoneyTo(closest);
		}
		break;
	case 4:
		//one-to-one atack
		for (Piece* piece : myPieces)
		{
			Piece* closest = ClosestPieceByLableTransform(BestPieces(), piece);
			if (closest != nullptr && closest->GetPriceToConquer(this) <= piece->GetMoney())
				piece->TransferMoneyTo(closest);
		}
	}
}

void Bot::EarnMoneyAtPiece(Piece* piece, float& timePassed)
{
	int earnings = round(timePassed / time_to_make_money);
	piece->AddMoney(earnings);
	timePassed -= time_to_make_money * earnings;
}

vector<Piece*> Bot::BestPieces()
{
	vector<Piece*> bestPieces;
	int price = INT_MAX;
	for (Piece* piece : oblast->GetPieces())
	{
		if ((piece->owner != PieceOwner::BotAsOwner || piece->botOwner != this))
		{
			if (piece->GetPriceToConquer(this) < price)
			{
				bestPieces.clear();
				bestPieces.push_back(piece);
				price = piece->GetPriceToConquer(this);
			}
			else if(piece->GetPriceToConquer(this) == price)
				bestPieces.push_back(piece);
		}
	}
	return bestPieces;
}

int Bot::TotalMoney()
{
	int money = 0;
	for (Piece* piece : oblast->GetPieces())
		if (piece->owner == PieceOwner::BotAsOwner && piece->botOwner == this)
			money += piece->GetMoney();
	return money;
}

vector<Piece*> Bot::MyPieces()
{
	vector<Piece*> pieces;
	for (Piece* piece : oblast->GetPieces())
		if (piece->owner == PieceOwner::BotAsOwner && piece->botOwner == this)
			pieces.push_back(piece);
	return pieces;
}

vector<Piece*> Bot::ClosestPiecesByNumber(vector<Piece*> pieces)
{
	vector<Piece*> myPieces = MyPieces();
	vector<Piece*> closest;
	int minDif = INT_MAX;
	int difSum = 0;
	for (Piece* piece : pieces)
	{
		int pieceNum = piece->get_name().to_int();
		for (Piece* mine : myPieces)
			difSum += abs(mine->get_name().to_int() - pieceNum);
		if (difSum < minDif)
		{
			minDif = difSum;
			difSum = 0;
			closest.clear();
			closest.push_back(piece);
		}
		else if(difSum==minDif)
			closest.push_back(piece);
	}
	return closest;


}

Piece* Bot::ClosestPieceByLableTransform(vector<Piece*> pieces)
{
	vector<Piece*> myPieces = MyPieces();
	Piece* closest = nullptr;
	int minDif = INT_MAX;
	int difSum = 0;
	for (Piece* piece : pieces)
	{
		for (Piece* mine : myPieces)
		{
			difSum += cast_to<SmartLabel>(piece->get_node("SmartLabel"))->get_global_position().distance_to(cast_to<SmartLabel>(mine->get_node("SmartLabel"))->get_global_position());
		}
		if (difSum < minDif)
		{
			minDif = difSum;
			closest = piece;
		}
			difSum = 0;
	}
	return closest;
}

Piece* Bot::ClosestPieceByLableTransform(vector<Piece*> pieces, Piece* from)
{
	Piece* closest = nullptr;
	int minDif = INT_MAX;
	int dif = 0;
	for (Piece* piece : pieces)
	{
		dif = cast_to<SmartLabel>(piece->get_node("SmartLabel"))->get_global_position().distance_to(cast_to<SmartLabel>(from->get_node("SmartLabel"))->get_global_position());
		if (dif < minDif)
		{
			minDif = dif;
			closest = piece;
		}
	}
	return closest;
}
