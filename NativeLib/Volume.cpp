#include "Volume.h"

void Volume::_register_methods()
{
	register_method("_ready", &Volume::_ready);
	register_method("_HSlider_value_changed", &Volume::_HSlider_value_changed);

	register_property("bus_name", &Volume::bus_name, (String)"");
}

void Volume::_init()
{
	audioserver = AudioServer::get_singleton();
}

void Volume::_ready()
{
	connect("value_changed", this, "_HSlider_value_changed");
	set_value(audioserver->get_bus_volume_db(audioserver->get_bus_index(bus_name)));
}

void Volume::_HSlider_value_changed(float value)
{
	audioserver->set_bus_volume_db(audioserver->get_bus_index(bus_name), value);
	//DataLoader::GetSingleton()->SaveSettingsData();
}