#include "Player.h"

void Player::_register_methods()
{
	register_property("money_speed", &Player::money_speed, 1.0f);
	register_property("time_to_make_money", &Player::time_to_make_money, 1.0f);
}

void Player::_init()
{
	instance = this;
}

void Player::EarnMoneyAtPiece(Piece* piece, float &timePassed)
{
	int earnings = round(timePassed / time_to_make_money);
	piece->AddMoney(earnings);
	timePassed -= time_to_make_money * earnings;
}

Player* Player::GetSingleton()
{
	return instance;
}
