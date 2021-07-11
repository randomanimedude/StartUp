#include "Oblast.h"

void Oblast::_register_methods()
{
	register_method("_input_event", &Oblast::_input_event);
	register_method("_ready", &Oblast::_ready);
	register_method("_physics_process", &Oblast::_physics_process);

	register_property("LevelNumber", &Oblast::LevelNumber, -1);
	register_property("LevelPrice", &Oblast::LevelPrice, -1);
	register_property("first_time_reward", &Oblast::first_time_reward, 100);
	register_property("repeated_reward", &Oblast::repeated_reward, 10);
}

void Oblast::_init()
{
}

void Oblast::_ready()
{
	dataLoader = DataLoader::GetSingleton();

	gameManager = GameManager::GetSingleton();
	mainSprite = Node::cast_to<MeshInstance2D>(get_node("Sprite"));
	collisionShape = Node::cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));

	currentColor = get_self_modulate();

	IsOpen = DataLoader::GetSingleton()->ReturnLevelStatus(LevelNumber);

	if (IsOpen == 2)
		set_self_modulate(blue);

	LockAnimation = Node::cast_to<AnimationPlayer>(get_node("Lock/AnimationPlayer"));
	LockSprite = Node::cast_to<Sprite>(get_node("Lock/Sprite"));

	if (IsOpen == 0)
	{
		set_self_modulate(gray);
		LockSprite->set_visible(true);
	}

	else
		LockSprite->set_visible(false);

	if (!DataLoader::GetSingleton()->IsTutorialStepCompleted(0))
	{
		cast_to<Node2D>(get_node("../../UI/Tutorial1/Tutorial1"))->set_visible(true);
		gameManager->tutorialWindowIsOpen = true;
	}

	currentColor = get_self_modulate();
}

void Oblast::_physics_process()
{
	switch (state)
	{
	case Hiding:

		if (IsOpen == 0)
			LockAnimation->play((String)"Hide");

		currentColor.a = lerp(currentColor.a, 0, transition_t);

		if (currentColor.a < 0.01)
		{
			currentColor.a = 0;
			state = Hidden;
			mainSprite->set_visible(false);
		}
		break;
	case Appearing:

		if (IsOpen == 0)
			LockAnimation->play((String)"Appearance");

		currentColor.a = lerp(currentColor.a, 1, transition_t);

		if (currentColor.a > 0.99)
		{
			currentColor.a = 1;
			state = Visible;
		}
		break;
	case VisibleToBG:
		currentColor = lerp(currentColor, borderColor, transition_t);
		if (abs(currentColor.r - borderColor.r) * abs(currentColor.g - borderColor.g) * abs(currentColor.b - borderColor.b) < 0.000000000001)
		{
			if (!DataLoader::GetSingleton()->IsTutorialStepCompleted(1))
			{
				cast_to<Node2D>(get_node("../../UI/Tutorial2/Tutorial2"))->set_visible(true);
				gameManager->tutorialWindowIsOpen = true;
			}

			if (!gameManager->tutorialWindowIsOpen)
			{
				currentColor = borderColor;
				state = BG;
				gameManager->SetGameIsPlaying(true);
				ResetCameraButton::GetSingleton()->SetEnabled(true);
			}
		}
		break;
	case BGToVisible:
		currentColor = lerp(currentColor, storedColor, transition_t);
		if (abs(currentColor.r - storedColor.r) * abs(currentColor.g - storedColor.g) * abs(currentColor.b - storedColor.b) < 0.000000000001)
		{
			currentColor = storedColor;
			state = Visible;
			piecesCombined = nullptr;
			pieces.clear();
		}
	}
	mainSprite->set_self_modulate(currentColor);
}

void Oblast::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && !get_tree()->is_input_handled() &&
		!gameManager->IsGamePlaying() && IsOpen == 1 && !gameManager->tutorialWindowIsOpen && !dataLoader->ReturnWindowsStatus())
	{
		if (gameManager->GetSelectedOblast() == nullptr)
			gameManager->SelectOblast(this);

		get_tree()->set_input_as_handled();
	}

	else if (event->is_pressed() && IsOpen == 0 && !dataLoader->ReturnWindowsStatus())
		LevelPurchase::GetSingleton()->ShowLevelInfo(LevelNumber, LevelPrice, 1, 1);
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

	bool toReturn = !(pieces.size() - controlledByPlayer);

	if (toReturn)
	{
		storedColor = blue;
		Complete();
	}
	return toReturn;
}

Piece* Oblast::GetSelectedPiece()
{
	return selectedPiece;
}

void Oblast::Open()
{
	LockSprite->set_visible(false);
	ChangeColorTo(Color(1,1,1,1),1);
	IsOpen = 1;
	
	DataLoader::GetSingleton()->OpenLevel(LevelNumber);
}

void Oblast::Close()
{
	LockSprite->set_visible(true);
	ChangeColorTo(gray,1);
	IsOpen = 0;

	DataLoader::GetSingleton()->CloseLevel(LevelNumber);
}

void Oblast::Complete()
{
	ChangeColorTo(blue, 1);
	IsOpen = 2;

	DataLoader::GetSingleton()->CompleteLevel(LevelNumber);


	if (!DataLoader::GetSingleton()->IsTutorialStepCompleted(2))
	{
		cast_to<Node2D>(get_node("../../UI/Tutorial3/Tutorial3"))->set_visible(true);
		gameManager->tutorialWindowIsOpen = true;
	}
}