#include "Piece.h"

void Piece::_register_methods()
{
	register_method("_ready", &Piece::_ready);
	register_method("_physics_process", &Piece::_physics_process);
	register_method("_input_event", &Piece::_input_event);

	register_property("money_to_unlock", &Piece::moneyToUnlock, 10);
	register_property("start_as_player", &Piece::startAsPlayer, false);
}

void Piece::_init()
{
}

void Piece::_ready()
{
	text = cast_to<LabelText>(get_node("SmartLabel"));
	collider = cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));
	sprite = cast_to<MeshInstance2D>(get_node("Sprite"));
	oblast = cast_to<Oblast>(get_node("../.."));
	oblast->RegisterPiece(this);
	gameManager = GameManager::GetSingleton();

	if (startAsPlayer)
	{
		//_owner = gameManager->player;
		text->SetValue(money);
	}
	else
	{
		text->SetValue(moneyToUnlock);
	}

	if (_owner != nullptr)
	{
		//currentColor = _owner->ownerColor;
		//currentColor.a = 0;
	}
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
		break;
	case Visible:
		if (gameManager->IsGamePlaying())
		{

		}
	}
	sprite->set_self_modulate(currentColor);
}

void Piece::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && !get_tree()->is_input_handled())
	{
		if (oblast->IsPieceSelected(this))
			oblast->UnselectPiece();
		else
			oblast->SelectPiece(this);
		get_tree()->set_input_as_handled();
	}
}

void Piece::Show()
{
	state = Appearing;
}

void Piece::Hide()
{
}

void Piece::UpdateSituation()
{
}

void Piece::AddMoney(int amount)
{
	money += amount;
}


