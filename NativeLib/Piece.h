#pragma once
#include "CommonLib.h"
#include "Oblast.h"
#include "GameManager.h"
#include <Area2D.hpp>
#include <MeshInstance2D.hpp>
#include <CollisionPolygon2D.hpp>
#include <InputEventMouseButton.hpp>

class Oblast;
class GameManager;

class Piece : public Area2D
{
	GODOT_CLASS(Piece, Area2D);

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _physics_process();
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
	void Show();
	void Hide();
	void UpdateSituation();

private:
	MeshInstance2D* sprite;
	CollisionPolygon2D* collider;
	Oblast* oblast;
	GameManager* gameManager;

	State state = Hidden;

	Color def = Color(255, 255, 255, 255) / 255.0;
	Color blue = Color(97, 168, 239, 255) / 255.0;
	Color currentColor = Color(1, 1, 1, 0);
};

