#pragma once

#include "CommonLib.h"
#include <Node.hpp>
#include "CameraController.h"
#include "Oblast.h"
#include <ResourceLoader.hpp>

class Oblast;
class CameraController;

class GameManager :
    public Node
{
	GODOT_CLASS(GameManager, Node);

public:
	static void _register_methods();
	void _init();

	static GameManager* GetSingleton();
	void _ready();

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

