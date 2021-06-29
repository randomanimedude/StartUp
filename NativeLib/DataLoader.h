#pragma once
#include "CommonLib.h"
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Dictionary.hpp>
#include <Variant.hpp>

class DataLoader : public Node
{
	GODOT_CLASS(DataLoader, Node);

public:
	static void _register_methods();
	void _init();

	void _ready();

	void _process(float delta);

	static DataLoader* GetSingleton();
	void LoadGameCurrencyData();
	void SaveGameCurrencyData();
	void UpdateMainCurrency(int value);
	int ReturnMainCurrency() { return MainCurrency; };

private:
	const String ProgressFile = "user://progress.save";

	static inline DataLoader* instance;
	int MainCurrency = 0;
};