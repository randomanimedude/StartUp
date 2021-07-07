#pragma once
#include <Node2D.hpp>
#include <Button.hpp>

#include "CommonLib.h"
#include "DataLoader.h"
#include "Oblast.h"
#include "MainCurrency.h"
class ResetButtons : 
	public Node2D
{
	GODOT_CLASS(ResetButtons, Node2D);

public:
	static void _register_methods();
	void _init();

	void _on_ResetValuteButton_pressed();
	void _on_ResetLevelProgres_pressed();
	void _on_ResetAllProgres_pressed();
	void _on_AddValute_pressed();
};

