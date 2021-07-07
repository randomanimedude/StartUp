#include "TutorialWindow.h"

void TutorialWindow::_register_methods()
{
	register_method("_ready", &TutorialWindow::_ready);
	register_method("Close", &TutorialWindow::Close);

	register_property("tutorial_step", &TutorialWindow::tutorial_step, 1);
}

void TutorialWindow::_init()
{
}

void TutorialWindow::_ready()
{
	dataLoader = DataLoader::GetSingleton();

	//set_visible(!dataLoader->IsTutorialStepCompleted(tutorial_step));

	cast_to<TextureButton>(get_node("TextureButton"))->connect("pressed", this, "Close");
}

void TutorialWindow::Close()
{
	if (!dataLoader->IsTutorialStepCompleted(tutorial_step))
	{
		set_visible(false);
		dataLoader->CompleteTutorialStep(tutorial_step);
		dataLoader->SaveTutorialProgres();
	}
	GameManager::GetSingleton()->tutorialWindowIsOpen = false;
}
