#include "ProfileButton.h"

void ProfileButton::_register_methods()
{
	register_method("_on_ProfileButton_pressed", &ProfileButton::_on_ProfileButton_pressed);
	register_method("_ready", &ProfileButton::_ready);
}

void ProfileButton::_init()
{
	connect("pressed", this, "_on_ProfileButton_pressed");
}

void ProfileButton::_ready()
{
	dataLoader = DataLoader::GetSingleton();

	upgradeMenu = cast_to<Node2D>(get_node("../UpgradeMenu"));
}

void ProfileButton::_on_ProfileButton_pressed()
{
	if (!upgradeMenu->is_visible() && !dataLoader->ReturnWindowsStatus() || !upgradeMenu->is_visible() && !dataLoader->ReturnWindowsStatusOnLevels())
	{
		upgradeMenu->set_visible(true);

		if (dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatusOnLevels(true);

		else if (!dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatus(true);
	}

	else if (upgradeMenu->is_visible())
	{
		upgradeMenu->set_visible(false);	

		if (dataLoader->ReturnIsLevelPlaying())
			dataLoader->SetWindowsStatusOnLevels(false);
		else
			dataLoader->SetWindowsStatus(false);
	}
}
