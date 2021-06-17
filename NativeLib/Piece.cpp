#include "Piece.h"

void Piece::_register_methods()
{
	register_method("_ready", &Piece::_ready);
	register_method("_physics_process", &Piece::_physics_process);
}

void Piece::_init()
{
}

void Piece::_ready()
{
	collider = cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));
	sprite = cast_to<MeshInstance2D>(get_node("Sprite"));
	oblast = cast_to<Oblast>(get_node("../.."));
	oblast->RegisterPiece(this);
}

void Piece::_physics_process()
{
	switch (state)
	{
	case Hiding:
		currentColor = Color(currentColor.r, currentColor.g, currentColor.b, lerp(currentColor.a, 0, transition_t));
		if (currentColor.a < 0.01)
		{
			currentColor = Color(1, 1, 1, 0);
			state = Hidden;
		}
		break;
	case Appearing:
		currentColor = Color(currentColor.r, currentColor.g, currentColor.b, lerp(currentColor.a, 1, transition_t));
		if (currentColor.a > 0.99)
		{
			currentColor = Color(1, 1, 1, 1);
			state = Visible;
		}
	}
	sprite->set_modulate(currentColor);
}

void Piece::Show()
{
	state = Appearing;
}

void Piece::Hide()
{
}


