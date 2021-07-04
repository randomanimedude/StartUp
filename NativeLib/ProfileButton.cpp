#include "ProfileButton.h"

void ProfileButton::_register_methods()
{
	register_method("_on_ProfileButton_pressed", &ProfileButton::_on_ProfileButton_pressed);
}

void ProfileButton::_init()
{
	connect("pressed", this, "_on_ProfileButton_pressed");
}

void ProfileButton::_on_ProfileButton_pressed()
{
	Node2D* upgradeMenu = cast_to<Node2D>(get_node("../UpgradeMenu"));
	upgradeMenu->set_visible(!upgradeMenu->is_visible());
}
