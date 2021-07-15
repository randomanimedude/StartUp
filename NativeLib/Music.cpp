#include "Music.h"

void Music::_register_methods()
{
	register_method("_ready", &Music::_ready);
}

void Music::_init()
{
}

void Music::_ready()
{
	set_volume_db(-20);
	play();
}


