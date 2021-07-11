#pragma once
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Dictionary.hpp>
#include <Variant.hpp>

#include "CommonLib.h"
#include "MainCurrency.h"
#include "UpgradeButton.h"

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

	//Player upgrades
	void LoadPlayerUpgrades();
	void SavePlayerUpgrades();
	void ResetPlayerUpgrades();

	//Condition of windows
	void SetWindowsStatus(bool Status);
	bool ReturnWindowsStatus();
	void SetWindowsStatusOnLevels(bool Status);
	bool ReturnWindowsStatusOnLevels();
	void SetIsLevelPlaying(bool Status);
	bool ReturnIsLevelPlaying();

private:
	const String Currency = "user://Currency.save";
	const String LevelsStatusPath = "user://LevelsStatus.save";
	const String TutorialStatus = "user://Tutorial.save";
	const String PlayerUpgrades = "user://PlayerUpgrades.save";
	const String WindowsStatusPath = "user://WindowsStatus.save";
	const String WindowsStatusOnLevelsPath = "user://WindowsStatusOnLevels.save";
	const String IsLevelPlayingPath = "user://IsLevelPlaying.save";

	int MainCurrency = 0;

	int money_speed_bought = 0;
	int time_to_make_money_bought = 0;

	//0 - the level is closed
	//1 - the level is open
	//2 - the level is complete
	int LevelsStatus[24];

	bool tutorialProgress[3];

	// true - some window is open, false - not open
	bool WindowsStatus;
	bool WindowsStatusOnLevels;
	bool IsLevelPlaying;

	static inline DataLoader* instance;
};