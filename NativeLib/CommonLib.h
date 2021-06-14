#pragma once

#include <Godot.hpp>
#include <Color.hpp>

using namespace godot;
using namespace std;

enum State { Visible, Hidden, BG, Appearing, Hiding, VisibleToBG, BGToVisible };

float lerp(float a, float b, float t);
Color lerp(Color a, Color b, float t);

float const transition_t = 0.2;