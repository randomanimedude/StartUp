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

	//The main currency
	void LoadGameCurrency();
	void SaveGameCurrency();
	void UpdateMainCurrency(int value);
	int ReturnMainCurrency() { return MainCurrency; };

	//Levels progres
	void LoadLevelsProgres();
	void SaveLevelsProgres();
	void ResetLevelsProgresAvailability();
	bool ReturnLevelStatus(int Number);
	void OpenLevel(int Number);

private:
	const String ProgressFile = "user://progress.save";

	static inline DataLoader* instance;
	int MainCurrency = 0;

	bool LevelsProgres[24];
};