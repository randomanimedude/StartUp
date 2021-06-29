#include "Piece.h"

void Piece::_register_methods()
{
	register_method("_ready", &Piece::_ready);
	register_method("_physics_process", &Piece::_physics_process);
	register_method("_input_event", &Piece::_input_event);

	register_property("money_to_conquer", &Piece::moneyToConquer, 10);
	register_property("start_as_player", &Piece::start_as_player, false);
	register_property("start_as_bot", &Piece::start_as_bot, false);
	register_property("bot_number", &Piece::bot_number, 1);
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
	player = Player::GetSingleton();

	if (start_as_player)
	{
		text->SetValue(money);
		currentColor = Player::GetSingleton()->color;
		owner = PieceOwner::PlayerAsOwner;
	}
	else if (start_as_bot)
	{
		text->SetValue(money);
		botOwner = cast_to<Bot>(get_node(NodePath((String)"../Bot" + String::num(bot_number))));
		currentColor = botOwner->color;
		owner = PieceOwner::BotAsOwner;
	}
	else
	{
		text->SetValue(moneyToConquer);
		currentColor = defaultColor;
		owner = PieceOwner::None;
	}
}

void Piece::_physics_process(float delta)
{
	switch (state)
	{
	case Hiding:
		currentColor.a = lerp(currentColor.a, 0, transition_t);
		if (currentColor.a < 0.01)
		{
			currentColor.a = 0;
			state = Hidden;
		}
		break;
	case Appearing:
		currentColor.a = lerp(currentColor.a, 1, transition_t);
		if (currentColor.a > 0.99)
		{
			currentColor.a = 1;
			state = Visible;
		}
		break;
	case Visible:
		if (gameManager->IsGamePlaying())
		{
			switch (owner)
			{
			case PlayerAsOwner:
				//currentColor = player->color;
				timeSinceLastEarning += delta;
				player->EarnMoneyAtPiece(this, timeSinceLastEarning);
				break;
			case BotAsOwner:
				//currentColor = botOwner->color;
				timeSinceLastEarning += delta;
				botOwner->EarnMoneyAtPiece(this, timeSinceLastEarning);
				break;
			case None:
				break;
			default:
				break;
			}
		}
	}
	sprite->set_self_modulate(currentColor);
}

void Piece::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && !get_tree()->is_input_handled())
	{
		Piece* selectedPiece = oblast->GetSelectedPiece();
		cout << owner << endl;
		switch (owner)
		{
		case PlayerAsOwner:
			if (selectedPiece != nullptr)
			{
				if (selectedPiece != this)
					selectedPiece->TransferMoneyTo(this);
				oblast->UnselectPiece();
			}
			else
				oblast->SelectPiece(this);
			break;
		case BotAsOwner:
			break;
		case None:
			if (selectedPiece != nullptr)
				selectedPiece->TransferMoneyTo(this);
			break;
		default:
			break;
		}
		get_tree()->set_input_as_handled();
	}
}

void Piece::Show()
{
	currentColor.a = 0;
	state = Appearing;
}

void Piece::Hide()
{
	currentColor.a = 1;
	state = Hiding;
}

void Piece::UpdateSituation()
{
}

void Piece::AddMoney(int amount)
{
	money += amount;
	text->SetValue(money);
}

void Piece::TransferMoneyTo(Piece* piece)
{
	if (money > 0)
	{
		if (piece->owner == this->owner)
			piece->AddMoney(money);
		else
			piece->Conquer(money, this);
		money = 0;
	}
	oblast->UnselectPiece();
}

void Piece::Conquer(int money, Piece* conqueror)
{
	if (owner == PieceOwner::None)
	{
		if (tryingToConquer == conqueror->owner || tryingToConquer == PieceOwner::None)		//continue old conquer
		{
			int dif = min(moneyToConquer - conquerProgress, money);
			conquerProgress += dif;
			money -= dif;
			tryingToConquer = conqueror->owner;
			text->SetValue(moneyToConquer - conquerProgress);
			UpdateConquerProgressColor();
			if (moneyToConquer == conquerProgress)
			{
				owner = tryingToConquer;
				tryingToConquer = PieceOwner::None;
				AddMoney(money);
			}
			GameManager::GetSingleton()->CheckIfOblastIsCompleted();
		}
		else																				//stop someone else's conquer
		{
			int dif = min(conquerProgress, money);
			conquerProgress -= dif;
			money -= dif;
			text->SetValue(moneyToConquer - conquerProgress);
			UpdateConquerProgressColor();
			if (conquerProgress == 0)
				tryingToConquer = PieceOwner::None;
			if (money > 0)
				Conquer(money, conqueror);
		}
	}
}

void Piece::UpdateConquerProgressColor()
{
	if (tryingToConquer == PieceOwner::PlayerAsOwner)
		currentColor = lerp(defaultColor, Player::GetSingleton()->color, (float)conquerProgress / moneyToConquer);
}

int Piece::GetPriceToConquer()
{
	return money + moneyToConquer;
}
