#ifndef CONFIGS_H
#define CONFIGS_H

#include "player.hpp"
#include "enemy.hpp"
#include "shoot.hpp"

struct GameConfig {
    bool gameOver;
    bool pause;
    int score;
    bool victory;


    int shootRate;
    float alpha;

    int activeEnemies;
    int enemiesKill;
    bool smooth;

    GameConfig();
};

#endif
