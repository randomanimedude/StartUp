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
	register_property("NumbOfBots", &Oblast::NumbOfBots, 2);
	register_property("BotsComplexity", &Oblast::BotsComplexity, (String)"easy");
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

	Animator = cast_to<AnimationPlayer>(get_node(NodePath((String)"/root/Node2D/Animator")));
	AdditionalAnim = cast_to<Label>(get_node(NodePath((String)"/root/Node2D/AdditionalAnim")));

	currentColor = get_self_modulate();

	LevelStatus = DataLoader::GetSingleton()->ReturnLevelStatus(LevelNumber);

	if (LevelStatus == 2)
		currentColor = blue;

	LockAnimation = Node::cast_to<AnimationPlayer>(get_node("Lock/Animator"));
	LockSprite = Node::cast_to<Sprite>(get_node("Lock/Sprite"));

	if (LevelStatus == 0)
	{
		currentColor = MainCurrency::GetSingleton()->ReturnValue() >= LevelPrice ? lightGray : gray;			//gray for closed, light gray for closed that can be bought
		LockSprite->set_visible(true);
	}

	else
		LockSprite->set_visible(false);

	if (!DataLoader::GetSingleton()->IsTutorialStepCompleted(0))
	{
		cast_to<Node2D>(get_node("../../UI/Tutorial1/Tutorial1"))->set_visible(true);
		gameManager->tutorialWindowIsOpen = true;
	}
}

void Oblast::_physics_process()
{
	switch (state)
	{
	case Hiding:

		if (LevelStatus == 0)
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

		if (LevelStatus == 0)
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
		break;
	default:
		UpdateAvailabilityColor();							//light gray if player can unlock
	}
	mainSprite->set_self_modulate(currentColor);
}

void Oblast::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (LevelStatus == 1 || LevelStatus == 2)
		if (event->is_pressed() && !get_tree()->is_input_handled() &&
		!gameManager->IsGamePlaying() && !gameManager->tutorialWindowIsOpen && !dataLoader->ReturnWindowsStatus())
	{
		if (gameManager->GetSelectedOblast() == nullptr)
			gameManager->SelectOblast(this);

		get_tree()->set_input_as_handled();
	}

		if (event->is_pressed() && LevelStatus == 0 && !dataLoader->ReturnWindowsStatus())
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
	for (int i = piecesCombined->get_child_count() - 1; i >= 0; --i)
	{
		if (cast_to<Node>(piecesCombined->get_child(i))->get_name().find("FlyingMoney") != -1)
			cast_to<Node>(piecesCombined->get_child(i))->queue_free();
	}
}

void Oblast::RegisterPiece(Piece* piece)
{
	pieces.push_back(piece);
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

	if(pieces.size()==controlledByBot)
		gameManager->UnselectOblast();	//go to map at defeat

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
	//LockSprite->set_visible(false);
	if (LevelNumber != 1)
	LockAnimation->play((String)"LockOpening");
	ChangeColorTo(Color(1, 1, 1, 1), 1);
	LevelStatus = 1;
	
	DataLoader::GetSingleton()->OpenLevel(LevelNumber);
}

void Oblast::Close()
{
	LockSprite->set_visible(true);
	ChangeColorTo(MainCurrency::GetSingleton()->ReturnValue() >= LevelPrice ? lightGray : gray, 1);
	LevelStatus = 0;

	DataLoader::GetSingleton()->CloseLevel(LevelNumber);
}

void Oblast::Complete()
{
	if (dataLoader->ReturnLevelStatus(LevelNumber) == 1)
	{
		MainCurrency::GetSingleton()->AddValue(first_time_reward);
		AdditionalAnim->set_text((String)"+" + String::num(first_time_reward));
	}
		
	else
	{
		MainCurrency::GetSingleton()->AddValue(repeated_reward);
		AdditionalAnim->set_text((String)"+" + String::num(repeated_reward));
	}

	Animator->play(String("AddValute"));

	ChangeColorTo(blue, 1);
	LevelStatus = 2;

	DataLoader::GetSingleton()->CompleteLevel(LevelNumber);


	if (!DataLoader::GetSingleton()->IsTutorialStepCompleted(2))
	{
		cast_to<Node2D>(get_node("../../UI/Tutorial3/Tutorial3"))->set_visible(true);
		gameManager->tutorialWindowIsOpen = true;
	}
}

void Oblast::UpdateAvailabilityColor()
{
	if (LevelStatus == 0)
	{
		currentColor = MainCurrency::GetSingleton()->ReturnValue() >= LevelPrice ? lightGray : gray;
	}
}
