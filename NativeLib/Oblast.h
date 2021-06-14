#pragma once

#include "CommonLib.h"
#include "GameManager.h"
#include <Area2D.hpp>
#include <InputEventMouseButton.hpp>
#include <GlobalConstants.hpp>
#include <Sprite.hpp>
#include <MeshInstance2D.hpp>
#include <Texture.hpp>
#include <CollisionPolygon2D.hpp>
#include <SceneTree.hpp>

class GameManager;

enum OblastState {Visible, Hidden, Appearing, Hiding};

class Oblast :
    public Area2D
{
	GODOT_CLASS(Oblast, Area2D);

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _physics_process();
	void _input_event(Node* viewport, InputEventMouseButton* event, int shape_idx);
	void ChangeColorTo(Color color, float force);
	Vector2 GetSize();
	void Hide();
	void Show();

private:
	MeshInstance2D* mainSprite;
	Sprite* border;
	CollisionPolygon2D* collisionShape;
	GameManager* gameManager;

	float colorChangeForce = 0;

	Color def = Color(255, 255, 255, 255)/255.0;
	Color blue = Color(97, 168, 239, 255)/255.0;

	OblastState state = Visible;
};

