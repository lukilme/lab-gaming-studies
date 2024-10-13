#include "enemy.hpp"

Enemy::Enemy() : active(false), speed({0, 0}), color({0, 255, 0, 255}), body({0, 0, 50, 50}) {}

Enemy::Enemy(bool active, Vector2 enemySpeed, Color enemyColor) {
    this->active = active;
    this->speed = enemySpeed;
    this->color = enemyColor;
    this->body = {0, 0, 50, 50};
}
