#include "Oblast.h"

void Oblast::_register_methods()
{
	register_method("_input_event", &Oblast::_input_event);
	register_method("_ready", &Oblast::_ready);
}

void Oblast::_init()
{
}

void Oblast::_ready()
{
	mainSprite = cast_to<MeshInstance2D>(get_node("Sprite"));
	border = cast_to<Sprite>(get_node("Border"));
	collisionShape = cast_to<CollisionPolygon2D>(get_node("CollisionPolygon2D"));
}

void Oblast::_physics_process()
{
	/*switch (state)
	{
	case Hiding:
		mainSprite->set_self_modulate(Color(1, 1, 1, lerp(mainSprite->get_self_modulate().a, 0, transition_t)));
		if (mainSprite->get_self_modulate().a < 0.01)
			mainSprite->set_self_modulate(Color(1, 1, 1, 0));
		break;
	case Appearing:
		mainSprite->set_self_modulate(Color(1, 1, 1, lerp(mainSprite->get_self_modulate().a, 1, transition_t)));
		if (mainSprite->get_self_modulate().a > 0.99)
			mainSprite->set_self_modulate(Color(1, 1, 1, 1));
	}*/
}

void Oblast::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && !get_tree()->is_input_handled())
	{
		//border->set_visible(!border->is_visible());
		ChangeColorTo(blue, 0.1);
		//Hide();
		GameManager::GetSingleton()->SelectOblast(this);
		get_tree()->set_input_as_handled();
	}
}

void Oblast::ChangeColorTo(Color color, float force)
{
	if ((colorChangeForce += force) > 1)
		colorChangeForce = 1;
	mainSprite->set_self_modulate(def-(def-color)*colorChangeForce);
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
	state = Appearing;
}
