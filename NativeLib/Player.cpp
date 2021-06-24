#include "Player.h"

void Player::_register_methods()
{
}

void Player::_init()
{
	instance = this;
}

void Player::EarnMoneyAtPiece(Piece* piece, float &timePassed)
{
	int earnings = round(timePassed / timeToMakeMoney);
	piece->AddMoney(earnings);
	timePassed -= timeToMakeMoney * earnings;
}

Player* Player::GetSingleton()
{
	return instance;
}
