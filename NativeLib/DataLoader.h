#pragma once
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Dictionary.hpp>
#include <Variant.hpp>

#include "CommonLib.h"
#include "MainCurrency.h"

class DataLoader : public Node
{
	GODOT_CLASS(DataLoader, Node);

public:
	static void _register_methods();
	void _init();
	void _ready();

	static DataLoader* GetSingleton();

	//The main currency
	void LoadGameCurrency();
	void SaveGameCurrency();
	void UpdateMainCurrency(int value);
	int ReturnMainCurrency() { return MainCurrency; };

	//Levels progres
	void LoadLevelsProgres();
	void SaveLevelsProgres();
	void ResetLevelsProgres();
	int ReturnLevelStatus(int Number);
	void OpenLevel(int Number);
	void CompleteLevel(int Number);
	void CloseLevel(int Number);

	//Tutorial progress
	void LoadTutorialProgres();
	void SaveTutorialProgres();
	void ResetTutorialProgress();
	bool IsTutorialStepCompleted(int step);
	void CompleteTutorialStep(int step);

private:
	const String Currency = "user://Currency.save";
	const String LevelsStatusPath = "user://LevelsStatus.save";
	const String TutorialStatus = "user://Tutorial.save";

	int MainCurrency = 0;

	//0 - the level is closed
	//1 - the level is open
	//2 - the level is complete
	int LevelsStatus[24];

	bool tutorialProgress[3];

	static inline DataLoader* instance;
};