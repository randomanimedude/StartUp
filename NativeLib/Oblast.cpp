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
}

void Oblast::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && event->get_button_index() == GlobalConstants::BUTTON_LEFT)
	{
		//border->set_visible(!border->is_visible());
		changeColorTo(blue, 0.1);
	}
}

void Oblast::changeColorTo(Color color, float force)
{
	if ((colorChangeForce += force) > 1)
		colorChangeForce = 1;
	mainSprite->set_self_modulate(def-(def-color)*colorChangeForce);
}
