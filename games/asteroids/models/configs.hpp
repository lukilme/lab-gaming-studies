#ifndef CONFIGS_H
#define CONFIGS_H


struct GameConfig {
    bool gameOver;
    bool pause;
    int score;
    bool victory;

    float alpha;
    int shootRate;

    int activeEnemies;
    int enemiesKill;
    bool smooth;

    GameConfig();
};

#endif
