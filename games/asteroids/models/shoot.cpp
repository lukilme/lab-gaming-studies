#include "shoot.hpp"

Shoot::Shoot() : active(false), speed({0, 0}), color({255, 255, 255, 0}), body({0, 0, 10, 10}) {}

Shoot::Shoot(bool active, Vector2 shootSpeed, Color shootColor) {
    this->active = active;
    this->speed = shootSpeed;
    this->color = shootColor;
    this->body = {0, 0, 10, 10};
}
