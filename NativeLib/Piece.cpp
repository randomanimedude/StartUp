#include "Piece.h"

void Piece::_register_methods()
{
}

void Piece::_init()
{
	collider = cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));
	sprite = cast_to<MeshInstance2D>(get_node("Sprite"));
}
