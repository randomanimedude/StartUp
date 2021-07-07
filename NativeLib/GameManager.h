#pragma once
#include <Node.hpp>
#include <ResourceLoader.hpp>

#include "CommonLib.h"
#include "CameraController.h"
#include "Oblast.h"
#include "DataLoader.h"


class Oblast;
class CameraController;

class GameManager :
    public Node
{
	GODOT_CLASS(GameManager, Node);

public:
	static void _register_methods();
	void _init();
	void _ready();

	static GameManager* GetSingleton();

	void SelectOblast(Oblast* oblast);
	void UnselectOblast();
	bool IsGamePlaying() { return gameIsPlaying; }
	void SetGameIsPlaying(bool playing);
	void CheckIfOblastIsCompleted();
	Oblast* GetSelectedOblast() { return selectedOblast; }

	Ref<PackedScene> flyingMoney;
	bool tutorialWindowIsOpen = false;

private:
	static inline GameManager* instance;

	CameraController* camera;

	Oblast* oblasti[24];
	Oblast* selectedOblast = nullptr;

	bool gameIsPlaying = false;

};

