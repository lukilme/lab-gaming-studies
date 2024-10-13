#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "raylib.h"

class Enemy {
private:

public:
    Rectangle body;
    Vector2 speed;
    bool active;
    Color color;
    Enemy();
    Enemy(bool active, Vector2 enemySpeed, Color enemyColor);
    // Outros métodos, se necessários
};

#endif
