#include "ProfileButton.h"

void ProfileButton::_register_methods()
{
	register_method("_on_ProfileButton_pressed", &ProfileButton::_on_ProfileButton_pressed);
	register_method("_ready", &ProfileButton::_ready);

	register_property("window_name", &ProfileButton::window_name, (String)"UpgradeMenu");
}

void ProfileButton::_init()
{
	connect("pressed", this, "_on_ProfileButton_pressed");
}

void ProfileButton::_ready()
{
	dataLoader = DataLoader::GetSingleton();

	ButtonsSound = cast_to<AudioStreamPlayer>(get_node(NodePath((String)"/root/Node2D/ButtonsSound")));

	window = cast_to<Node2D>(get_node(NodePath("../"+window_name)));
}

void ProfileButton::_on_ProfileButton_pressed()
{
	if (!window->is_visible() && !dataLoader->ReturnWindowsStatus() || !window->is_visible() && !dataLoader->ReturnWindowsStatusOnLevels())
	{
		window->set_visible(true);

		ButtonsSound->stop();
		ButtonsSound->play();

		if (dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatusOnLevels(true);

		else if (!dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatus(true);

		get_tree()->set_pause(true);
	}

	else if (window->is_visible())
	{
		window->set_visible(false);

		ButtonsSound->stop();
		ButtonsSound->play();

		if (dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatusOnLevels(false);
		else
			dataLoader->SetWindowsStatus(false);

		get_tree()->set_pause(false);
	}
}
