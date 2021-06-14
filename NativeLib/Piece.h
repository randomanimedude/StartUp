#pragma once
#include "CommonLib.h"
#include <Area2D.hpp>
#include <MeshInstance2D.hpp>
#include <CollisionPolygon2D.hpp>

class Piece : public Area2D
{
	GODOT_CLASS(Piece, Area2D);

public:
	static void _register_methods();
	void _init();

private:
	MeshInstance2D* sprite;
	CollisionPolygon2D* collider;
};

