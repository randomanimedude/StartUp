#pragma once
#include "Piece.h"

class Piece;

class PieceOwner
{
public:
	virtual void EarnMoney(Piece* piece, float &timePassed) = 0;

	//Color ownerColor;

private:
	//float timeToEarnMoney;
};

class Player : public PieceOwner
{
public:
	virtual void EarnMoney(Piece* piece, float &timePassed);

	//Color ownerColor = Color(97, 168, 239, 255) / 255.0;	//player is blue
private:
	//float timeToEarnMoney = 1;
};

