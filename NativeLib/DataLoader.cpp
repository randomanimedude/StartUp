#include "DataLoader.h"

void DataLoader::_register_methods()
{
	register_method("_ready", &DataLoader::_ready);
}

void DataLoader::_init()
{
	instance = this;
}

void DataLoader::_ready()
{
	Ref<File> file = File::_new();

	//Main currency
	if (file->file_exists(Currency))
		LoadGameCurrency();
	else
		MainCurrency = 0;

	//Levels status
	if (file->file_exists(LevelsStatus))
		LoadLevelsProgres();
	else
		ResetLevelsProgres();

	MainCurrency::GetSingleton()->SetValue(MainCurrency);

	//Tutorial
	if (file->file_exists(TutorialStatus))
		LoadTutorialProgres();
	else
		ResetTutorialProgress();
}

DataLoader* DataLoader::GetSingleton()
{
	return instance;
}

//
//Game currency
//

void DataLoader::LoadGameCurrency()
{
	Ref<File> file = File::_new();
	if (file->file_exists(Currency))
	{
		file->open(Currency, file->READ);
		//load and parse json string
		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		MainCurrency = rez[(String)"MainCurrency"];
	}
}

void DataLoader::SaveGameCurrency()
{
	Ref<File> file = File::_new();
	file->open(Currency, file->WRITE);

	//create dictionary with data and save it as json
	Dictionary dict;
	dict[(String)"MainCurrency"] = MainCurrency;
	file->store_string(dict.to_json());
	file->close();
}

void DataLoader::UpdateMainCurrency(int value)
{
	MainCurrency = value;
	SaveGameCurrency();
}

//
//Levels progres
//

void DataLoader::LoadLevelsProgres()
{
	Ref<File> file = File::_new();
	if (file->file_exists(LevelsStatus))
	{
		file->open(LevelsStatus, file->READ);
		//load and parse json string
		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		for (int i = 0; i < 24; i++)
			LevelsProgres[i] = rez[(String)"Level#" + String::num_int64(i)];
	}
}

void DataLoader::SaveLevelsProgres()
{
	Ref<File> file = File::_new();
	file->open(LevelsStatus, file->WRITE);

	//create dictionary with data and save it as json
	Dictionary dict;
	for (int i = 0; i < 24; i++)
		dict[(String)"Level#" + String::num_int64(i)] = LevelsProgres[i];
	file->store_string(dict.to_json());
	file->close();
}

void DataLoader::ResetLevelsProgres()
{
	for (int i = 0; i < 24; i++)
		LevelsProgres[i] = false;

	LevelsProgres[23] = true;

	SaveLevelsProgres();
}

bool DataLoader::ReturnLevelStatus(int Number)
{
	return LevelsProgres[Number - 1];
}

void DataLoader::OpenLevel(int Number)
{
	LevelsProgres[Number - 1] = true;
	SaveLevelsProgres();
}

//
//Tutorial progres
//

void DataLoader::LoadTutorialProgres()
{
	Ref<File> file = File::_new();
	if (file->file_exists(TutorialStatus))
	{
		file->open(TutorialStatus, file->READ);

		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		for (int i = 0; i < 3; ++i)
			tutorialProgress[i] = rez[(String)"Tutorial" + String::num_int64(i)];
	}
}

void DataLoader::SaveTutorialProgres()
{
	Ref<File> file = File::_new();
	file->open(TutorialStatus, file->WRITE);

	Dictionary dict;
	for (int i = 0; i < 3; i++)
		dict[(String)"Tutorial" + String::num_int64(i)] = tutorialProgress[i];
	file->store_string(dict.to_json());
	file->close();
}

void DataLoader::ResetTutorialProgress()
{
	for (bool& tutorial : tutorialProgress)
		tutorial = false;
	SaveTutorialProgres();
}

bool DataLoader::IsTutorialStepCompleted(int step)
{
	return (step<3 && step>-1) ? tutorialProgress[step] : false;
}

void DataLoader::CompleteTutorialStep(int step)
{
	if (step<3 && step>-1)
		tutorialProgress[step] = true;
}
