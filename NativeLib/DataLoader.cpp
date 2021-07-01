#include "DataLoader.h"

void DataLoader::_register_methods()
{
	register_method("_ready", &DataLoader::_ready);
	register_method("_process", &DataLoader::_process);
}

void DataLoader::_init()
{
	instance = this;

	Ref<File> file = File::_new();
	if (file->file_exists(ProgressFile))
	{
		LoadGameCurrency();
		LoadLevelsProgres();
		//ResetLevelsProgresAvailability();
	}
	else
		ResetLevelsProgresAvailability();
}

void DataLoader::_process(float delta)
{

}

void DataLoader::_ready()
{
	
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
	if (file->file_exists(ProgressFile))
	{
		file->open(ProgressFile, file->READ);
		//load and parse json string
		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		MainCurrency = rez[(String)"MainCurrency#"];
	}
}

void DataLoader::SaveGameCurrency()
{
	Ref<File> file = File::_new();
	file->open(ProgressFile, file->WRITE);

	//create dictionary with data and save it as json
	Dictionary dict;
	dict[(String)"MainCurrency#"] = MainCurrency;
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
	if (file->file_exists(ProgressFile))
	{
		file->open(ProgressFile, file->READ);
		//load and parse json string
		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		for (int i = 0; i < 24; i++)
			LevelsProgres[i] = rez[(String)"Level#" + String::num_int64(i)];
		LevelsProgres[23] = true;
	}
}

void DataLoader::SaveLevelsProgres()
{
	Ref<File> file = File::_new();
	file->open(ProgressFile, file->WRITE);

	//create dictionary with data and save it as json
	Dictionary dict;
	for (int i = 0; i < 24; i++)
		dict[(String)"Level#" + String::num_int64(i)] = LevelsProgres[i];
	file->store_string(dict.to_json());
	file->close();
}

void DataLoader::ResetLevelsProgresAvailability()
{
	for (int i = 0; i < 23; i++)
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