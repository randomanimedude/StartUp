#pragma once
#include "CommonLib.h"
#include "DataLoader.h"
#include <HSlider.hpp>
#include <AudioServer.hpp>

class Volume :
    public HSlider
{
    GODOT_CLASS(Volume, HSlider);

    String bus_name = "";

public:
    static void _register_methods();
    void _init();
    void _ready();
    void _HSlider_value_changed(float value);
    AudioServer* audioserver;
};
