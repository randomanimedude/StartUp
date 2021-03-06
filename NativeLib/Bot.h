#pragma once
#include <Node.hpp>

#include "CommonLib.h"
#include "Piece.h"
//#include "Oblast.h"

class Piece;
class Oblast;

class Bot :
    public Node
{
	GODOT_CLASS(Bot, Node);
	
	int color_r = 255;
	int color_g = 255;
	int color_b = 255;
	float update_t = 2;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(float delta);

	void DoStuff();
	void EarnMoneyAtPiece(Piece* piece, float& timePassed);

	Color color;

	float money_speed = 1;

private:
	vector<Piece*> BestPieces();
	vector<Piece*> MyPieces();
	vector<Piece*> ClosestPiecesByNumber(vector<Piece*> pieces);
	Piece* ClosestPieceByLableTransform(vector<Piece*> pieces);
	Piece* ClosestPieceByLableTransform(vector<Piece*> pieces, Piece* from);

	int TotalMoney();

	Oblast* oblast;

	float timePassed = 0;
	float time_to_make_money = 1;
};

