#ifndef SHOOT_HPP
#define SHOOT_HPP

#include "raylib.h"

class Shoot {
private:
    
public:
    Rectangle body;
    Vector2 speed;
    bool active;
    Color color;
    Shoot();
    Shoot(bool active, Vector2 shootSpeed, Color shootColor);
    // Outros métodos, se necessários
};

#endif
