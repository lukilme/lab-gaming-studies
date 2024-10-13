#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include <string>

class Player {
private:

public:
    std::string name;
    Vector2 speed;
    Color color;
    Rectangle body;
    Player();
    Player(const std::string& playerName, Vector2 playerSpeed, Color playerColor);
    // Outros métodos, se necessários
};

#endif
