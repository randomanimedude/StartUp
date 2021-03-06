#pragma once
#include <Area2D.hpp>
#include <MeshInstance2D.hpp>
#include <CollisionPolygon2D.hpp>
#include <InputEventMouseButton.hpp>

#include "GameManager.h"
#include "SmartLabel.h"
#include "Player.h"
#include "Bot.h"
#include "FlyingMoney.h"
#include "CommonLib.h"
#include "Oblast.h"

class FlyingMoney;
class Bot;
class Player;
class Oblast;
class GameManager;

class Piece : public Area2D
{
	GODOT_CLASS(Piece, Area2D);

	int moneyToConquer = 10;
	bool start_as_player = false;
	bool start_as_bot = false;
	int bot_number = 1;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _physics_process(float delta);
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);

	void Show();
	void Hide();

	void AddMoney(int amount);
	int GetMoney() { return money; }
	void TransferMoneyTo(Piece* piece);
	void Conquer(int moneyCome, PieceOwner conquerorOwner, Bot* conquerorBotOwner);
	void UpdateConquerProgressColor();
	int GetPriceToConquer(Bot* bot);
	PieceOwner owner;

	Bot* botOwner = nullptr;
	Bot* botConqueror = nullptr;

private:
	MeshInstance2D* sprite;
	CollisionPolygon2D* collider;
	Oblast* oblast;
	GameManager* gameManager;
	SmartLabel* text;
	Player* player = nullptr;

	State state = Hidden;

	PieceOwner tryingToConquer = PieceOwner::None;
	int conquerProgress = 0;

	Color currentColor;

	int money = 0;
	float timeSinceLastEarning = 0;

	DataLoader* dataLoader;
};

