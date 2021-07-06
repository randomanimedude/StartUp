#pragma once
#include <Node2D.hpp>
#include <Button.hpp>

#include "CommonLib.h"
#include "MainCurrency.h"
#include "DataLoader.h"
#include "Oblast.h"

class TemporaryButtons : 
	public Node2D
{
	GODOT_CLASS(TemporaryButtons, Node2D);

public:

	static void _register_methods();
	void _init();

	void _on_CloseAllLevels_pressed();
	
};

