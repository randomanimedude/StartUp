#pragma once
#include "CommonLib.h"
#include "Oblast.h"
#include "GameManager.h"
#include <Area2D.hpp>
#include <MeshInstance2D.hpp>
#include <CollisionPolygon2D.hpp>
#include <InputEventMouseButton.hpp>
#include "LabelText.h"
#include "Player.h"

class Player;
class Oblast;
class GameManager;

class Piece : public Area2D
{
	GODOT_CLASS(Piece, Area2D);

	int moneyToConquer = 10;
	bool startAsPlayer = false;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _physics_process(float delta);
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
	void Show();
	void Hide();
	void UpdateSituation();
	void AddMoney(int amount);
	void TransferMoneyTo(Piece* piece);
	void Conquer(int money, Piece* conqueror);
	void UpdateConquerProgressColor();
	PieceOwner owner;

private:
	MeshInstance2D* sprite;
	CollisionPolygon2D* collider;
	Oblast* oblast;
	GameManager* gameManager;
	LabelText* text;

	State state = Hidden;

	PieceOwner tryingToConquer = PieceOwner::None;
	int conquerProgress = 0;

	Color currentColor;

	int money = 0;
	float timeSinceLastEarning = 0;
};

