#include "player.hpp"

Player::Player() : name("Unnamed"), speed({0, 0}), color({255, 255, 255, 255}), body({0, 0, 30, 30}) {}

Player::Player(const std::string& playerName, Vector2 playerSpeed, Color playerColor) {
    this->name = playerName;
    this->speed = playerSpeed;
    this->color = playerColor;
    this->body = {5, 5, 30, 30};
}
