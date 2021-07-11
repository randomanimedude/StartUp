#include "FlyingMoney.h"

void FlyingMoney::_register_methods()
{
	register_method("_physics_process", &FlyingMoney::_physics_process);
}

void FlyingMoney::_init()
{

}

void FlyingMoney::_physics_process(float delta)
{
	if (proceed)
	{
		progress += speed;
		if (progress < 1)
		{
			set_global_position(lerp(fromPos, toPos, progress));
		}
		else
		{
			if (toPiece->owner == owner && (owner == PlayerAsOwner || toPiece->botOwner == botOwner))
				toPiece->AddMoney(money);
			else
				toPiece->Conquer(money, owner, botOwner);


			queue_free();
		}
	}
}

void FlyingMoney::SetCourse(Piece* from, Piece* to, int amount, PieceOwner owner, Bot* botOwner)
{
	fromPos = cast_to<Label>(from->get_node("SmartLabel"))->get_global_position();
	set_global_position(fromPos);
	toPiece = to;
	toPos = cast_to<Label>(to->get_node("SmartLabel"))->get_global_position();
	this->owner = owner;
	money = amount;

	//sticking money from case based on amount of money (from 0 to numberOfStickingMoney)
	int stickingAmount = min((int)max((float)(money - minStickAmount) / (maxStickAmount - minStickAmount) * numberOfStickingMoney, 0.0f), numberOfStickingMoney);

	while (stickingAmount > 0)
	{
		cast_to<Node2D>(get_node(NodePath((String)"uah" + String::num(stickingAmount--))))->set_visible(true);
	}

	this->botOwner = botOwner;

	speed = (owner == PlayerAsOwner ? Player::GetSingleton()->money_speed : botOwner->money_speed) / fromPos.distance_to(toPos);
	cast_to<MeshInstance2D>(get_node("BackCase"))->set_self_modulate(owner == PlayerAsOwner ? Player::GetSingleton()->color : botOwner->color);

	proceed = true;
}
