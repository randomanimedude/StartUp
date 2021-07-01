#pragma once

#include <Godot.hpp>
#include <Color.hpp>

using namespace godot;
using namespace std;

enum State { Visible, Hidden, BG, Appearing, Hiding, VisibleToBG, BGToVisible };
enum PieceOwner { PlayerAsOwner, BotAsOwner, None };

float lerp(float a, float b, float t);
Color lerp(Color a, Color b, float t);
Vector2 lerp(Vector2 a, Vector2 b, float t);

float const transition_t = 0.2;

Color const defaultColor = Color(255, 255, 255, 255) / 255.0;
//Color const playerColor = Color(97, 168, 239, 255) / 255.0;