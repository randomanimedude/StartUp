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
		LoadGameCurrencyData();
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

void DataLoader::LoadGameCurrencyData()
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

void DataLoader::SaveGameCurrencyData()
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
	SaveGameCurrencyData();
}
