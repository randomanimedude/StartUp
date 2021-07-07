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
		ResetLevelsProgresAvailability();

	MainCurrency::GetSingleton()->SetValue(MainCurrency);
}

DataLoader* DataLoader::GetSingleton()
{
	return instance;
}

//
//Game currency
//

/// <summary>
/// Takes the value of the main currency from the file
/// </summary>
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

/// <summary>
/// Writes the value of the main currency to a file
/// </summary>
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

/// <summary>
/// Update and write to the file the value of the main currency
/// </summary>
void DataLoader::UpdateMainCurrency(int value)
{
	MainCurrency = value;
	SaveGameCurrency();
}

//
//Levels progres
//

/// <summary>
/// Read progress from file
/// </summary>
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

/// <summary>
/// Record progress to a file
/// </summary>
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

/// <summary>
/// Resetting progress
/// </summary>
void DataLoader::ResetLevelsProgresAvailability()
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