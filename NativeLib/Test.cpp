#include "Test.h"

void Test::_register_methods()
{
	register_method("_input_event", &Test::_input_event);
}

void Test::_init()
{
}

void Test::_input_event(Node* viewport, InputEventMouseButton* event, int shape_idx)
{
	if (event->is_pressed() && event->get_button_index() == GlobalConstants::BUTTON_LEFT)
		set_visible(false);
}

