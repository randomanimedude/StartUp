#pragma once

#include "CommonLib.h"
#include <Node.hpp>
#include "CameraController.h"
#include "Oblast.h"

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

private:
	static inline GameManager* instance;
	CameraController* camera;

};

