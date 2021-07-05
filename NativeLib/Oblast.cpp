#include "Oblast.h"

void Oblast::_register_methods()
{
	register_method("_input_event", &Oblast::_input_event);
	register_method("_ready", &Oblast::_ready);
	register_method("_physics_process", &Oblast::_physics_process);

	register_property("LevelNumber", &Oblast::LevelNumber, -1);
	register_property("LevelPrice", &Oblast::LevelPrice, -1);
}

void Oblast::_init()
{
}

void Oblast::_ready()
{
	gameManager = GameManager::GetSingleton();
	mainSprite = cast_to<MeshInstance2D>(get_node("Sprite"));
	collisionShape = cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));

	if (LevelNumber == 23)
	Lock = Node::cast_to<Sprite>(get_node("Lock"));

	currentColor = get_self_modulate();

	IsOpen = DataLoader::GetSingleton()->ReturnLevelStatus(LevelNumber);
	if (!IsOpen && LevelNumber != 24)
		ChangeColorTo(Color(128, 128, 128, 255)/255, 1);
}

void Oblast::_physics_process()
{
	switch (state)
	{
	case Hiding:
		//currentColor = Color(currentColor.r, currentColor.g, currentColor.b, lerp(currentColor.a, 0, transition_t));
		currentColor.a = lerp(currentColor.a, 0, transition_t);
		if (currentColor.a < 0.01)
		{
			//currentColor=Color(1, 1, 1, 0);
			currentColor.a = 0;
			state = Hidden;
			mainSprite->set_visible(false);

			if (LevelNumber == 23)
				Lock->set_visible(false);
		}
		break;
	case Appearing:
		//currentColor = Color(currentColor.r, currentColor.g, currentColor.b, lerp(currentColor.a, 1, transition_t));
		currentColor.a = lerp(currentColor.a, 1, transition_t);
		if (currentColor.a > 0.99)
		{
		/*	if (!IsOpen)
				currentColor = Color(0, 0, 0, 1);
			else
				currentColor = Color(1, 1, 1, 1);*/
			currentColor.a = 1;
			state = Visible;

			if (LevelNumber == 23)
				Lock->set_visible(true);
		}
		break;
	case VisibleToBG:
		currentColor = lerp(currentColor, borderColor, transition_t);
		if (abs(currentColor.r - borderColor.r) * abs(currentColor.g - borderColor.g) * abs(currentColor.b - borderColor.b) < 0.000000000001)
		{
			currentColor = borderColor;
			state = BG;
			gameManager->SetGameIsPlaying(true);
			ResetCameraButton::GetSingleton()->SetEnabled(true);
		}
		break;
	case BGToVisible:
		currentColor = lerp(currentColor, storedColor, transition_t);
		if (abs(currentColor.r - storedColor.r) * abs(currentColor.g - storedColor.g) * abs(currentColor.b - storedColor.b) < 0.000000000001)
		{
			currentColor = storedColor;
			state = Visible;
			if (piecesCombined != nullptr)
			{
				piecesCombined->queue_free();
				piecesCombined = nullptr;
				//ResetCameraButton::GetSingleton()->set_visible(false);
				//gameManager->SetGameIsPlaying(false);
			}
		}
	}
	mainSprite->set_self_modulate(currentColor);
}

void Oblast::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && !get_tree()->is_input_handled() && !gameManager->IsGamePlaying() && IsOpen)
	{
		//border->set_visible(!border->is_visible());
		//ChangeColorTo(blue, 0.1);
		//Hide();
		if(gameManager->GetSelectedOblast()==nullptr)
			gameManager->SelectOblast(this);

		get_tree()->set_input_as_handled();
	}
}

void Oblast::ChangeColorTo(Color color, float force)
{
		if ((colorChangeForce += force) > 1)
			colorChangeForce = 1;
		currentColor = def - (def - color) * colorChangeForce;
		mainSprite->set_self_modulate(currentColor);
}

Vector2 Oblast::GetSize()
{
	return mainSprite->get_texture()->get_size() * mainSprite->get_global_scale();
}

void Oblast::Hide()
{
	state = Hiding;
}

void Oblast::Show()
{
	mainSprite->set_visible(true);
	state = Appearing;
}

void Oblast::ShowPieces()
{
	Ref<PackedScene> temp = resourceLoader->load("res://Prefabs/Oblasti/" + get_name() + "/Pieces.tscn");
	piecesCombined = cast_to<Node2D>(temp->instance());
	add_child(piecesCombined);
	storedColor = currentColor;
	state = VisibleToBG;
	if(piecesCombined!=nullptr)
		piecesCombined->set_visible(true);
	for (Piece* piece : pieces)
		piece->Show();
}

void Oblast::HidePieces()
{
	state = BGToVisible;
	for (Piece* piece : pieces)
		piece->Hide();
}

void Oblast::RegisterPiece(Piece* piece)
{
	pieces.push_back(piece);
}

void Oblast::UpdateSituation()
{
}

void Oblast::SelectPiece(Piece* piece)
{
	UnselectPiece();
	selectedPiece = piece;
	piece->set_scale(Vector2(1.012, 1.012));
}

void Oblast::UnselectPiece()
{
	if (selectedPiece != nullptr)
	{
		selectedPiece->set_scale(Vector2(1, 1));
		selectedPiece = nullptr;
	}
}

bool Oblast::IsCompleted()
{
	int controlledByPlayer = 0;
	int controlledByBot = 0;
	for (Piece* piece : pieces)
	{
		switch (piece->owner)
		{
		case PieceOwner::PlayerAsOwner:
			++controlledByPlayer;
			break;
		case PieceOwner::BotAsOwner:
			++controlledByBot;
		}
	}
	return !(pieces.size() - controlledByPlayer);
}

Piece* Oblast::GetSelectedPiece()
{
	return selectedPiece;
}
