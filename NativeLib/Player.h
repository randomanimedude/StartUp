#pragma once

#include "CommonLib.h"
#include <Node.hpp>
#include "Piece.h"

class Piece;

class Player :
    public Node
{
    GODOT_CLASS(Player, Node);

public:
    static void _register_methods();
    void _init();

    void EarnMoneyAtPiece(Piece* piece, float &timePassed);

    static Player* GetSingleton();
    Color const color = Color(97, 168, 239, 255) / 255.0;

    float money_speed = 1.0f;
    float time_to_make_money = 1.0f;
private:
    static inline Player* instance;
};

