#pragma once

#include "CommonLib.h"

#include <AudioStreamPlayer.hpp>

class Music :
	public AudioStreamPlayer
{
	GODOT_CLASS(Music, AudioStreamPlayer);

public:
	static void _register_methods();
	void _init();
	void _ready();

};
